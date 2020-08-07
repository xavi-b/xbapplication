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
