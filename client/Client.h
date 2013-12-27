
#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QLCDNumber>
#include <QThread>
#include "LogSystem.h"

#include "MessageProviderJson.h"
#include "SubscriberZMQ.h"



class SubscribeWorker : public QObject
{
    Q_OBJECT
    
public:
    void setSubscriber( dmsg::dclient::Subscriber* subscriber);
    
public slots:
    void process();
    void stop();
   

signals:
    void finished();
    
private:
     dmsg::dclient::Subscriber* m_subscriber;
};





class SubscribeThread : public QThread
{
    Q_OBJECT
public:
    SubscribeThread(QObject* parent) 
        : QThread(parent)
    {
    
    }

    void setSubscriber( dmsg::dclient::Subscriber* subscriber)
    {
        m_subscriber = subscriber;
    }

private:
    void run() 
    {
        m_subscriber->run(9000);
    }
    
     dmsg::dclient::Subscriber* m_subscriber;
};

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
    void showEvent(QShowEvent *event);
private slots:
    void about();

signals:
    void stopWorker();
    
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
    
    QThread* m_thread;
    SubscribeWorker* m_worker;
    friend class ClientLogger;
    friend class SubscribeListener;
};

#endif
