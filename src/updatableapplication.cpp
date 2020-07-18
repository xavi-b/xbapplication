#include "updatableapplication.h"

namespace XB
{

void UpdatableApplication::updateDownloadedHandler(QNetworkReply* reply)
{
    emit updateDownloaded(reply->readAll());
    reply->deleteLater();
}

void UpdatableApplication::update(QUrl const& updateUrl)
{
    connect(&downloadManager, &QNetworkAccessManager::finished, this, &UpdatableApplication::updateDownloadedHandler);
    QNetworkRequest request(updateUrl);
    downloadManager.get(request);
}

bool UpdatableApplication::applyUpdate(QByteArray const& data)
{
    QFile updater(QStandardPaths::writableLocation(QStandardPaths::StandardLocation::TempLocation));
    if(updater.open(QIODevice::ReadWrite))
    {
        updater.write(data);
        updater.close();
        this->quit();
        QProcess::startDetached(QFileInfo(updater).filePath(), { QCoreApplication::applicationDirPath() });
        return true;
    }

    return false;
}

UpdatableApplication::UpdatableApplication(QString const& applicationName,
                                           QString const& organizationDomain,
                                           QString const& organizationName,
                                           int argc, char *argv[])
    : Application(applicationName,
                  organizationDomain,
                  organizationName,
                  argc, argv)
{

}

bool UpdatableApplication::doCheckForUpdates()
{
    if(this->checkForUpdates && this->shouldUpdate(this->updateUrl))
        this->update(this->updateUrl);

    return false;
}

}