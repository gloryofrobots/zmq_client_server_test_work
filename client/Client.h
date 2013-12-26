
#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QLCDNumber>
#include "LogSystem.h"
#include "Subscriber.h"

namespace dmsg
{
    class MessageProviderJson;
    namespace dclient
    {
        class SubscriberZMQ;
    }
}

class Client : public QMainWindow
{
    Q_OBJECT
    
private:
    class SubscribeListener : public dmsg::dclient::Subscriber::SubscribeListener
    {
    public:
        SubscribeListener(Client * client);
        virtual void update(const dmsg::dclient::Subscriber::State& state);     
    private:
        Client * m_client;
    };
    
    class ClientLogger : public dmsg::Logger
    {
    public:
        ClientLogger(Client * client);
        void log(dmsg::TRawConstString msg);
    private:
        Client * m_client;
    };
    
public:
    Client();
    ~Client();
    
protected:
    void closeEvent(QCloseEvent *event);
    
private slots:
    void about();
    
private:
    void createWidgets();
    void createActions();
    void createMenus();
    void createStatusBar();
    void initLogSystem();
    void readSettings();
    void writeSettings();
    
    void initSubscriber();
    
    void subscribe();
    void stop();
    
    void onLog(QString msg);
    void onUpdateState(const dmsg::dclient::Subscriber::State& state);
       
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *helpMenu;
    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    
    QAction *exitAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    
    QString m_toolbarText;
    QLCDNumber* m_lcdNumber;
    ClientLogger * m_logger;
    SubscribeListener * m_subscribeListener;
    dmsg::MessageProviderJson * m_provider;
    dmsg::dclient::SubscriberZMQ* m_subscriber;
    
    friend class ClientLogger;
    friend class SubscribeListener;
};

#endif
