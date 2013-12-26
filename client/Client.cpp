#include <QtGui>

#include "Client.h"
#include "LogSystem.h"
#include "MessageProviderJson.h"
#include "SubscriberZMQ.h"

using namespace dmsg;

Client::SubscribeListener::SubscribeListener(Client *client)
    : m_client(client)
{
}
/////////////////////////////////////////////////////////
void Client::SubscribeListener::update(const dclient::Subscriber::State &state)
{
}
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
    : m_subscriber(NULL)
    , m_subscribeListener(NULL)
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
    //stop here
    if(m_subscriber != NULL)
    {
        delete m_subscriber;
    }
    
    if(m_subscribeListener != NULL)
    {
        delete m_subscriber;
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
}
/////////////////////////////////////////////////////////
void Client::closeEvent(QCloseEvent *event)
{
    writeSettings();
    event->accept();
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
    m_subscriber = new dclient::SubscriberZMQ(m_provider, "DATETIME_SERVER");
    m_subscribeListener = new SubscribeListener(this);
    
    m_subscriber->addListener(m_subscribeListener);
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
}
/////////////////////////////////////////////////////////
