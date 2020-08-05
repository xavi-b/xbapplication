#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QLocalServer>
#include <QLocalSocket>
#include <QDataStream>
#include <QDir>
#include <QTranslator>

namespace XB
{

class Application : public QApplication
{
    Q_OBJECT
private:
    int connectionTimeout = 1000;
    QLocalServer localServer;
    QString defaultLocale = "en_US";
    QString currentLocale;
    QTranslator translator;

    void newConnectionHandler();

protected:
    void setCurrentLocale(QString const& s);
    virtual bool sendToUniqueInstance(QLocalSocket& localSocket);
    virtual void readyReadHandler();

public:
    Application(QString const& applicationName,
                QString const& organizationDomain,
                QString const& organizationName,
                int& argc, char *argv[]);

    bool checkUniqueInstance();
    QString getUniqueApplicationName() const;
    virtual void processArguments(QStringList const& args) = 0;

    virtual QString translationsDir() const;
    bool switchLocale(QString const& locale);
    QStringList getAvailableLocales() const;

    void setConnectionTimeout(int i) { this->connectionTimeout = i; }
    int getConnectionTimeout() const { return this->connectionTimeout; }
    void setDefaultLocale(QString const& s);
    QString getCurrentLocale();

    static Application* instance();

signals:

};

}

#endif // APPLICATION_H
