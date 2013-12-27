#include <QtGui>

#include "Client.h"
#include "LogSystem.h"
#include "MessageProviderJson.h"
#include "SubscriberZMQ.h"

using namespace dmsg;

SubscribeWorker::~SubscribeWorker()
{
    if(m_subscriber != NULL)
    {
        if(m_subscriber->isOnRun())
        {
            m_subscriber->stop();
        }
        
        delete m_subscriber;
    }
}

SubscribeWorker::SubscribeWorker(Client::SubscribeListener * subscribeListener,
                                         MessageProviderJson *provider)
    : m_subscribeListener(subscribeListener)
    , m_provider(provider)
{
}

void SubscribeWorker::process()
{
    m_subscriber = new dclient::SubscriberZMQ(m_provider, "DATETIME_SERVER");
    m_subscriber->addListener(m_subscribeListener);
    
    m_subscriber->run(9000);
    
}

void SubscribeWorker::stop()
{
    if (m_subscriber != NULL)
    {
        m_subscriber->stop();
    }
    emit finished();
}

//SubscribeListener
Client::SubscribeListener::SubscribeListener(Client *client)
    : m_client(client)
{
}
/////////////////////////////////////////////////////////
void Client::SubscribeListener::update(const dclient::Subscriber::State &state)
{
    m_client->onUpdateState(state);
}
//ClientLogger
/////////////////////////////////////////////////////////
Client::ClientLogger::ClientLogger(Client * client)
    : m_client(client)
{
}
///////////////////////////////////////////
void Client::ClientLogger::log(TRawConstString msg)
{
    m_client->onLog(msg);
}
/////////////////////////////////////////////////////////
Client::Client()
    : m_subscribeListener(NULL)
    , m_logger(NULL)
    , m_provider(NULL)
{
    createWidgets();
    
    initLogSystem();
    initSubscriber();
    
    readSettings();
    createActions();
    createMenus();
    createStatusBar();
}
/////////////////////////////////////////////////////////
Client::~Client()
{
    if(m_subscribeListener != NULL)
    {
        delete m_subscribeListener;
    }
    
    if(m_provider != NULL)
    {
        delete m_provider;
    }
    
    if(m_logger != NULL)
    {
        delete m_logger;
    }
    
    LogSystem::destroy();

    qDebug() << "~Client()";
}
/////////////////////////////////////////////////////////
void Client::closeEvent(QCloseEvent *event)
{
    writeSettings();
  
    m_subscribeThread->terminate();
    m_subscribeThread->wait();
    event->accept();
}
/////////////////////////////////////////////////////////
void Client::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    QCoreApplication::processEvents();
    
    m_subscribeThread = new SubscribeThread(this);
    m_subscribeThread->setSubscriber(m_subscribeListener, m_provider);
    //connect(this, SIGNAL(stopWorker()), m_subscribeThread, SLOT(quit()));
    //connect(m_subscribeThread, SIGNAL(finished()), m_subscribeThread, SLOT(deleteLater()));
    m_subscribeThread->start();
    
    /*m_worker = new SubscribeWorker(m_subscribeListener, m_provider);
    SubscribeWorker* worker = m_worker;
    m_thread = new QThread();
    QThread* thread = m_thread;
    worker->moveToThread(thread);
    
    connect(thread, SIGNAL(started()), worker, SLOT(process()));
    
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    
    connect(this, SIGNAL(stopWorker()), worker, SLOT(deleteLater()));
    
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    
    thread->start();*/
}
/////////////////////////////////////////////////////////
void Client::about()
{
    QMessageBox::about(this, tr("About Client"),
                       tr("The <b>Client</b> is a Client. That`s all."));
}
/////////////////////////////////////////////////////////
void Client::createWidgets()
{
    m_lcdNumber = new QLCDNumber(this);
    setCentralWidget(m_lcdNumber);
    m_lcdNumber->setDigitCount(20);
}
/////////////////////////////////////////////////////////
void Client::createActions()
{
    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
    
    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
    
    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}
/////////////////////////////////////////////////////////
void Client::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&Connection"));
    fileMenu->addAction(exitAct);
    
    menuBar()->addSeparator();
    
    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}
/////////////////////////////////////////////////////////
void Client::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}
/////////////////////////////////////////////////////////
void Client::initLogSystem()
{ 
    dmsg::LogSystem::keep(new dmsg::LogSystem());
    m_logger = new ClientLogger(this); 
    LogSystem::get()->addLogger(m_logger);
    //subscriber.run(9000);
}
/////////////////////////////////////////////////////////
void Client::initSubscriber()
{
    m_provider = new MessageProviderJson(); 
    m_subscribeListener = new SubscribeListener(this);
}
/////////////////////////////////////////////////////////
void Client::readSettings()
{
    QSettings settings("Trolltech", "Application Example");
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    resize(size);
    move(pos);
}
/////////////////////////////////////////////////////////
void Client::writeSettings()
{
    QSettings settings("Trolltech", "Application Example");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}
/////////////////////////////////////////////////////////
void Client::onLog(QString msg)
{
    qDebug() << msg;
}
/////////////////////////////////////////////////////////
void Client::onUpdateState(const dclient::Subscriber::State &state)
{
    if(state.message.timestamp == 0)
    {
        m_lcdNumber->display("0000-00-00 00-00-00");
        return;
    }
    
    QDateTime datetime = QDateTime::fromTime_t(state.message.timestamp);
    //qDebug() << datetime.toString(Qt::ISODate);
    m_lcdNumber->display(datetime.toString(Qt::ISODate));
}
/////////////////////////////////////////////////////////


