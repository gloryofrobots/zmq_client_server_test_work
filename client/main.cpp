#include <QtCore>
#include <QtGui>
#include <iostream>
#include <fstream>
#include <string>

#include "zmqhelpers.h"
#include "SubscriberZMQ.h"
#include "MessageProviderJson.h"
#include "SimpleLogger.h"
#include "Client.h"

int main(int argc, char *argv[]) {    
    
    QApplication app(argc, argv);
    Client client;
    client.show();
    return app.exec();
}
