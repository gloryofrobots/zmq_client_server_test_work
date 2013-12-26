#include <iostream>

#include "ServerZMQ.h"
#include "MessageProviderJson.h"
#include "SimpleLogger.h"

int main(int argc, char *argv[])
{
    dmsg::LogSystem::keep(new dmsg::LogSystem());
    dmsg::SimpleLogger * logger = new dmsg::SimpleLogger();
    dmsg::LogSystem::get()->addLogger(logger);
    
    dmsg::MessageProviderJson * provider = new dmsg::MessageProviderJson();
    dmsg::dserver::ServerZMQ server(provider, "DATETIME_SERVER");
    server.run(9000);
    
    delete provider;
    delete logger;
    dmsg::LogSystem::destroy();
}




  
