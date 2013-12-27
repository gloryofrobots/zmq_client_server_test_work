#include <QtGui>

#include "Client.h"
#include "LogSystem.h"
#include "MessageProviderJson.h"
#include "SubscriberZMQ.h"

using namespace dmsg;

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
    event->accept();
    stopSubscribe();
}
/////////////////////////////////////////////////////////
void Client::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    QCoreApplication::processEvents();
    startSubscribe();
  
}
/////////////////////////////////////////////////////////
void Client::about()
{
    QMessageBox::about(this, tr("About Client"),
                       tr("The <b>Client</b> is a Client. That`s all."));
}
/////////////////////////////////////////////////////////
void Client::reconnect()
{
    if(isOnSubscribe())
    {
        stopSubscribe();
    }
    
    startSubscribe();
}
/////////////////////////////////////////////////////////
void Client::createWidgets()
{
     /*m_lcdNumber = new QLCDNumber(this);
     m_lcdNumber->setDigitCount(20);
     setCentralWidget(m_lcdNumber);*/
     
     QWidget* window = new QWidget(this);
     
     m_lcdNumber = new QLCDNumber;
     m_lcdNumber->setDigitCount(20);
     m_statusLabel = new QLabel("STATUS");
     m_pingLabel = new QLabel("PING");
    
     QGridLayout *layout = new QGridLayout;
     layout->addWidget(m_lcdNumber, 0, 0, 1, 2);
     layout->addWidget(m_statusLabel, 1, 0);
     layout->addWidget(m_pingLabel, 1, 1);
  
     window->setLayout(layout);

     this->setCentralWidget(window);
}
/////////////////////////////////////////////////////////
void Client::createActions()
{
    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    reconnectAct = new QAction(tr("&Reconnect"), this);
    reconnectAct->setStatusTip(tr("Reconnect"));
    connect(reconnectAct, SIGNAL(triggered()), this, SLOT(reconnect()));
    
    disconnectAct = new QAction(tr("&Disconnect"), this);
    disconnectAct->setStatusTip(tr("Disconnect"));
    connect(disconnectAct, SIGNAL(triggered()), this, SLOT(stopSubscribe()));
    
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
    fileMenu->addAction(reconnectAct);
    fileMenu->addAction(disconnectAct);
    
    fileMenu->addSeparator();
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
}
/////////////////////////////////////////////////////////
void Client::initSubscriber()
{
    m_provider = new MessageProviderJson(); 
    m_subscribeListener = new SubscribeListener(this);
}
/////////////////////////////////////////////////////////
void Client::startSubscribe()
{
    if (isOnSubscribe() == true)
    {
        DMSG_LOGGER("Invalid startSubscribe() call thread is not NULL");
        stopSubscribe();
    }
    
    m_subscribeThread = new SubscribeThread();
    m_subscribeThread->setSubscriber(m_subscribeListener, m_provider);
    connect(m_subscribeThread, SIGNAL(finished()), m_subscribeThread, SLOT(deleteLater()));
    m_subscribeThread->start();
}
/////////////////////////////////////////////////////////
void Client::stopSubscribe()
{
    if (m_subscribeThread == NULL)
    {
        DMSG_LOGGER("Invalid stopSubscribe() call thread is NULL");
        return;
    }
    
    m_subscribeThread->terminate();
    m_subscribeThread->wait();
    m_subscribeThread = NULL;
}
/////////////////////////////////////////////////////////
bool Client::isOnSubscribe()
{
    return m_subscribeThread == NULL;
}
/////////////////////////////////////////////////////////
void Client::readSettings()
{
    QSettings settings("Trolltech", "Application Example");
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(500, 500)).toSize();
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
        m_pingLabel->setText("");
    }
    else
    {
        QDateTime datetime = QDateTime::fromTime_t(state.message.timestamp);
        //qDebug() << datetime.toString(Qt::ISODate);
        m_lcdNumber->display(datetime.toString(Qt::ISODate));
        
        QString ping = tr("Ping time: ") + QString::number(state.pingTime);
        m_pingLabel->setText(ping);
    }
    
    QString connectionType = tr("Connection is ");
    connectionType += state.status == dclient::Subscriber::OFFLINE ? tr("offline") : tr("online");

    m_statusLabel->setText(connectionType);
}
/////////////////////////////////////////////////////////


