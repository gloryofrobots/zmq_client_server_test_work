#ifndef SERVER_H
#define SERVER_H
#include "UUID.h"
#include "Message.h"
#define DSERVER_MESSAGE_MAX_LENGTH 128
namespace dmsg 
{
    namespace dserver
    {
        class Server
        {
        public:
            Server();
            virtual ~Server();
           
            bool run(TUInt port);
            
            TRawConstString getUUIDString();
        protected:  
            virtual bool _onInit(TUInt port) = 0;
            virtual bool _onUpdate() = 0;
            
            void getNewMessage();
            UUID* m_uuid;
        private:
            bool init(TUInt port);
            bool update();
            bool m_isRun;
            
        };
    }
}
#endif
