#include "ServerZMQ.h"

extern "C" 
{
#include "zmqhelpers.h"
}

namespace dmsg
{
    namespace dserver
    {
        ServerZMQ::ServerZMQ() 
            : Server()
            , m_context(0)
            , m_publisher(0)
        {
        }
        
        ServerZMQ::~ServerZMQ()
        {
            clear();
        }
        
        bool ServerZMQ::_onInit(TUInt port)
        {
            m_context = zmq_ctx_new();
            if (m_context == 0)
            {
                //LOG error
                return false;
            } 
            
            m_publisher = zmq_socket(m_context, ZMQ_PUB);
            if (m_publisher == 0)
            {
                //LOG error
                clear();
                return false;
            } 
            
            TChar address[20] = {'\0'};
            sprintf(address, "tcp://*:%u", port);
            int result = zmq_bind(m_publisher, address);
            if (result != 0)
            {
                clear();
                return false;
            }
            
            return true;
        }
        
        bool ServerZMQ::_onUpdate()
        {
            getNewMessage();
            return false;
        }
        
        void ServerZMQ::clear()
        {
            if (m_context != 0)
            {
                zmq_ctx_destroy(m_context);
                m_context = 0;
            }
            
            if (m_publisher != 0)
            {   
                zmq_close(m_publisher);
                m_publisher = 0;
            }
        }
    }
}








//#ifdef WIN32
//#include "../msinttypes/inttypes.h"
//#else
//#include <inttypes.h>
//#endif


//static uint64_t generateId(uint16_t v1, uint16_t v2, uint16_t v3, uint16_t v4)
//{ 
//   uint64_t id;
//   id = v1 | (((uint64_t)v2) << 16) | (((uint64_t)v3) << 32) | (((uint64_t)v4) << 48);
//   return id;
//}
/*
// Weather update server
// Binds PUB socket to tcp://*:5556
// Publishes random weather updates

#include "zhelpers.h"

int main (void)
{
// Prepare our context and publisher
void *context = zmq_ctx_new ();
void *publisher = zmq_socket (context, ZMQ_PUB);
int rc = zmq_bind (publisher, "tcp://*:5556");
assert (rc == 0);
rc = zmq_bind (publisher, "ipc://weather.ipc");
assert (rc == 0);

// Initialize random number generator
srandom ((unsigned) time (NULL));
while (1) {
// Get values that will fool the boss
int zipcode, temperature, relhumidity;
zipcode = randof (100000);
temperature = randof (215) - 80;
relhumidity = randof (50) + 10;

// Send message to all subscribers
char update [20];
sprintf (update, "%05d %d %d", zipcode, temperature, relhumidity);
s_send (publisher, update);
}
zmq_close (publisher);
zmq_ctx_destroy (context);
return 0;
}


*/
