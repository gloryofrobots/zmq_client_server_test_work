#include "ServerZMQ.h"
#include <iostream>

int main(int argc, char *argv[])
{
    dmsg::dserver::ServerZMQ server;
    server.run(9000);
}




  
