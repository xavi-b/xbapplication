#include "application.h"

namespace XB
{

Application::Application(QString const& applicationName,
                         QString const& organizationDomain,
                         QString const& organizationName,
                         int argc, char *argv[])
    : QApplication(argc, argv)
{
    this->setApplicationName(applicationName);
    this->setOrganizationDomain(organizationDomain);
    this->setOrganizationName(organizationName);
}

int Application::startRunning()
{
    if(this->uniqueInstance)
    {
        QLocalSocket localSocket;
        localSocket.connectToServer(this->getUniqueApplicationName());
        if(localSocket.waitForConnected(this->connectionTimeout))
        {
            QByteArray data;
            QDataStream ds(&data, QIODevice::WriteOnly);
            ds << this->arguments();
            localSocket.write(data);
            return localSocket.waitForBytesWritten(this->connectionTimeout) ? 0 : 1;
        }
        else
        {
            localServer.listen(this->getUniqueApplicationName());
            connect(&localServer, &QLocalServer::newConnection, this, &Application::newConnectionHandler);
        }
    }

    this->run();

    return this->exec();
}

QString Application::getUniqueApplicationName() const
{
    return QString("%1_%2_%3")
            .arg(this->applicationName())
            .arg(this->organizationDomain())
            .arg(this->organizationName());
}

void Application::newConnectionHandler()
{
    QLocalSocket* localSocket = localServer.nextPendingConnection();
    connect(localSocket, &QLocalSocket::readyRead, this, &Application::readyReadHandler);
    connect(localSocket, &QLocalSocket::disconnected, localSocket, &QLocalSocket::deleteLater);
}

void Application::readyReadHandler()
{
    QLocalSocket* localSocket = qobject_cast<QLocalSocket*>(this->sender());
    if(localSocket)
    {
        QStringList arguments;
        QByteArray data = localSocket->readAll();
        QDataStream ds(data);
        ds >> arguments;
        this->processArguments(arguments);
    }
}

QString Application::translationsDir() const
{
    return ":/translations";
}

bool Application::switchLocale(QString const& locale)
{
    if(this->getAvailableLocales().contains(locale))
    {
        this->removeTranslator(&this->translator);

        QString path = this->translationsDir() + "/" + locale + ".qm";
        if(translator.load(path))
            this->installTranslator(&translator);

        this->setCurrentLocale(this->defaultLocale);

        return true;
    }

    return false;
}

QStringList Application::getAvailableLocales() const
{
    QDir dir(this->translationsDir());
    QStringList tsFiles = dir.entryList(QStringList("*.qm"), QDir::Filter::Files);

    QStringList locales;
    locales << this->defaultLocale;
    for(int i = 0; i < tsFiles.size(); ++i)
    {
        QString locale = tsFiles[i];
        locale.truncate(locale.lastIndexOf('.'));
        locales << locale;
    }
    return locales;
}

void Application::setDefaultLocale(const QString& s)
{
    this->defaultLocale = s;
    if(this->currentLocale.isEmpty())
        this->setCurrentLocale(this->defaultLocale);
}

void Application::setCurrentLocale(const QString& s)
{
    this->currentLocale = s;
    QLocale::setDefault(this->currentLocale);
}

QString Application::getCurrentLocale()
{
    if(this->currentLocale.isEmpty())
        this->setCurrentLocale(this->defaultLocale);

    return this->currentLocale;
}

Application* Application::instance()
{
    return qobject_cast<Application*>(QCoreApplication::instance());
}

}
