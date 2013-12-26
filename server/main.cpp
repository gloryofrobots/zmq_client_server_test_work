#include "ServerZMQ.h"
#include "MessageProviderJson.h"
#include <iostream>

int main(int argc, char *argv[])
{
    dmsg::MessageProviderJson * provider = new dmsg::MessageProviderJson();
    dmsg::dserver::ServerZMQ server(provider, "DATETIME_SERVER");
    server.run(9000);
    delete provider;
}




  
