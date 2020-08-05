#include "updatableapplication.h"

namespace XB
{

void UpdatableApplication::updateDownloadedHandler(QNetworkReply* reply)
{
    this->applyUpdate(reply->readAll());
    reply->deleteLater();
}

void UpdatableApplication::update(QUrl const& updateUrl)
{
    connect(&this->downloadManager, &QNetworkAccessManager::finished, this, &UpdatableApplication::updateDownloadedHandler);
    QNetworkRequest request(updateUrl);
    request.setTransferTimeout(this->transferTimeout);
    this->downloadManager.get(request);
}

bool UpdatableApplication::applyUpdate(QByteArray const& data)
{
    QDir dir = QStandardPaths::writableLocation(QStandardPaths::StandardLocation::TempLocation);
    QFile updater(dir.filePath("updater"));
    if(updater.open(QIODevice::ReadWrite))
    {
        updater.write(data);
        updater.close();
        this->quit();
        QStringList args = this->arguments();
        args[0] = QCoreApplication::applicationFilePath();
        QProcess::startDetached(QFileInfo(updater).filePath(), args);
        return true;
    }

    return false;
}

UpdatableApplication::UpdatableApplication(QString const& applicationName,
                                           QString const& organizationDomain,
                                           QString const& organizationName,
                                           int& argc, char *argv[])
    : Application(applicationName,
                  organizationDomain,
                  organizationName,
                  argc, argv)
{

}

bool UpdatableApplication::checkForUpdates()
{
    if(this->shouldCheckForUpdates && this->shouldUpdate(this->updateUrl))
    {
        this->update(this->updateUrl);
        return true;
    }

    return false;
}

}
