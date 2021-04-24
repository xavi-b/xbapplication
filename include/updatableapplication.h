#ifndef UPDATABLEAPPLICATION_H
#define UPDATABLEAPPLICATION_H

#include <QUrl>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QStandardPaths>
#include <QProcess>
#include <QFile>
#include "application.h"
#include "export.h"

namespace XB
{

class XBAPPLICATION_EXPORT UpdatableApplication: public Application
{
    Q_OBJECT
private:
    bool shouldCheckForUpdates = true;
    QUrl updateUrl;
    QNetworkAccessManager downloadManager;
    int transferTimeout = 30000;

    void updateDownloadedHandler(QNetworkReply* reply);

protected:
    virtual bool shouldUpdate(QUrl const& updateUrl) const = 0;
    virtual void update(QUrl const& updateUrl);
    virtual bool applyUpdate(QByteArray const& data) = 0;

public:
    UpdatableApplication(QString const& applicationName,
                         QString const& organizationDomain,
                         QString const& organizationName,
                         int& argc, char *argv[]);

    virtual void processArguments(QStringList const& args) = 0;

    bool checkForUpdates();
    void setCheckForUpdates(bool b) { this->shouldCheckForUpdates = b; }
    void setUpdateUrl(QUrl const& url) { this->updateUrl = url; }
    void setTransferTimeout(int i) { this->transferTimeout = i; }
    int getTransferTimeout() const { return this->transferTimeout; }
};

}

#endif // UPDATABLEAPPLICATION_H
