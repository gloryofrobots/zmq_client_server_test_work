
#ifndef CLIENT_H
#define CLIENT_H

#include <QtDebug>
#include <QTimer>
#include <QMainWindow>
#include <QLCDNumber>
#include <QLabel>
#include <QThread>
#include "LogSystem.h"

#include "types.h"
#include "MessageProviderJson.h"
#include "SubscriberZMQ.h"

class SubscribeThread;

class Client : public QMainWindow
{
    Q_OBJECT
    
public:
    //////////////////////////////////////////////////////////////
    //It work`s on background thread and call update-gui proc in client
    class SubscribeListener : public dmsg::dclient::Subscriber::SubscribeListener
    {
    public:
        SubscribeListener(Client * client);
        virtual void update(const dmsg::dclient::Subscriber::State& state);     
    private:
        Client * m_client;
    };
    //////////////////////////////////////////////////////////////
    //send messages to client
    class ClientLogger : public dmsg::Logger
    {
    public:
        ClientLogger(Client * client);
        void log(dmsg::TRawConstString msg);
    private:
        Client * m_client;
    };
    //////////////////////////////////////////////////////////////
public:
    Client();
    ~Client();
    
protected:
    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent *event);
private slots:
    void about();
    void reconnect();
    void startSubscribe();
    void stopSubscribe();
    
    //slot for checking connection timeout
    void connectionTimerOut();
signals:
    void stopWorker();
    
private:
    //intitialisers
    void createWidgets();
    void createActions();
    void createMenus();
    void createStatusBar();
    void initLogSystem();
    void readSettings();
    void writeSettings();
    
    void initSubscriber();
    void initDefaultConditions();
    
    //check if exist active background thread
    bool isOnSubscribe();
    
    //update connection status
    void updateStatus(bool isOnline);
    
    //update ping time label. if pingTime < 0 set empty string
    void updatePingTime(long pingTime);
    
    //update LCD Number
    void updateDate(dmsg::TTimeStamp timestamp);
    
    void updateLogView(const dmsg::dclient::Subscriber::State& state);
    
    //write messages to label
    void onLog(QString msg);
    void onUpdateState(const dmsg::dclient::Subscriber::State& state);
    
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *helpMenu;
    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    
    QAction *disconnectAct;
    QAction *reconnectAct;
    QAction *exitAct;
    QAction *aboutAct;
    QAction *aboutQtAct;

    QLabel * m_statusLabel;
    QLabel * m_pingLabel;
    QLabel * m_logLabel;
    QLCDNumber* m_lcdNumber;
    ClientLogger * m_logger;
    
    SubscribeListener * m_subscribeListener;
    dmsg::MessageProviderJson * m_provider;
    
    SubscribeThread * m_subscribeThread;
    QThread* m_thread;
    QTimer * m_timer;
    friend class ClientLogger;
    friend class SubscribeListener;
};

//run subscriber client in background
class SubscribeThread : public QThread
{
    Q_OBJECT
    
public:
   virtual ~SubscribeThread()
    {
        if(m_subscriber != NULL)
        {
            if(m_subscriber->isOnRun())
            {
                m_subscriber->stop();
            }
            
            qDebug() << "~SubscribeThread()";
            delete m_subscriber;
        }
    }

    void setSubscriber( Client::SubscribeListener * subscribeListener, dmsg::MessageProviderJson * provider)
    {
       m_subscribeListener = subscribeListener;
       m_provider = provider;
    }

private:
    void run() 
    {
         m_subscriber = new dmsg::dclient::SubscriberZMQ(m_provider, "DATETIME_SERVER");
         m_subscriber->addListener(m_subscribeListener);
         m_subscriber->run(9000);
    }

   Client::SubscribeListener * m_subscribeListener;
   dmsg::MessageProviderJson * m_provider;
   dmsg::dclient::Subscriber* m_subscriber;
};

#endif
