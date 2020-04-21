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
    bool uniqueInstance = false;
    int connectionTimeout = 1000;
    QLocalServer localServer;
    QString defaultLocale = "en_US";
    QString currentLocale;
    QTranslator translator;

protected:
    void setCurrentLocale(QString const& s);

public:
    Application(QString const& applicationName,
                QString const& organizationDomain,
                QString const& organizationName,
                int argc, char *argv[]);

    virtual int startRunning();
    QString getUniqueApplicationName() const;
    void newConnectionHandler();
    void readyReadHandler();
    virtual void run() = 0;
    virtual void processArguments(QStringList const& args) = 0;

    virtual QString translationsDir() const;
    bool switchLocale(QString const& locale);
    QStringList getAvailableLocales() const;

    void setUniqueInstance(bool b) { this->uniqueInstance = b; }
    void setConnectionTimeout(int i) { this->connectionTimeout = i; }
    void setDefaultLocale(QString const& s);
    QString getCurrentLocale();

    static Application* instance();

signals:

};

}

#endif // APPLICATION_H
