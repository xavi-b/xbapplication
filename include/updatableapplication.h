#ifndef UPDATABLEAPPLICATION_H
#define UPDATABLEAPPLICATION_H

#include <QUrl>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QStandardPaths>
#include <QProcess>
#include "application.h"

namespace XB
{

class UpdatableApplication: public Application
{
    Q_OBJECT

private:
    bool checkForUpdates = true;
    QUrl updateUrl;
    QNetworkAccessManager downloadManager;
    int transferTimeout = 30000;

    void updateDownloadedHandler(QNetworkReply* reply);

protected:
    virtual bool shouldUpdate(QUrl const& updateUrl) = 0;
    virtual void update(QUrl const& updateUrl);
    virtual bool applyUpdate(QByteArray const& data);

public:
    UpdatableApplication(QString const& applicationName,
                         QString const& organizationDomain,
                         QString const& organizationName,
                         int argc, char *argv[]);

    bool doCheckForUpdates();
    void setCheckForUpdates(bool b) { this->checkForUpdates = b; }
    void setUpdateUrl(QUrl const& url) { this->updateUrl = url; }
    void setTransferTimeout(int i) { this->transferTimeout = i; }
    int getTransferTimeout() const { return this->transferTimeout; }

signals:
    void updateDownloaded(QByteArray const& data);
};

}

#endif // UPDATABLEAPPLICATION_H
