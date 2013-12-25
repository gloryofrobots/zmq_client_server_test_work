#ifndef SERVERZMQ_H
#define SERVERZMQ_H
#include "Server.h"

namespace dmsg 
{
    namespace dserver
    {
        class ServerZMQ : public Server
        {
        public:
            ServerZMQ();
            virtual ~ServerZMQ();
            
        protected:
            virtual bool _onInit(TUInt port);
            virtual bool _onUpdate();
            
            void * m_context;
            void * m_publisher;
        private:
            void clear();
        };    
    }
}
#endif
