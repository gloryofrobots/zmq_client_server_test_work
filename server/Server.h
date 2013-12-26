#ifndef SERVER_H
#define SERVER_H
#include "UUID.h"
#include "MessageProvider.h"
#define DSERVER_MESSAGE_MAX_LENGTH 128
namespace dmsg 
{
    namespace dserver
    {
        class Server
        {
        public:
            Server(MessageProvider * messageProvider, const TString & subscribeId);
            virtual ~Server();
            
            bool run(TUInt port);
            
            TRawConstString getUUIDString();
        protected:  
            virtual bool _onInit(TUInt port) = 0;
            virtual bool _onUpdate() = 0;
            
            const TString& createNewMessageString();
            const TString& getSubscribeId();
            
        private:
            bool init(TUInt port);
            bool update();
            bool m_isRun;
            
            MessageProvider * m_messageProvider;
            UUID* m_uuid;
            Message m_message;
            TString m_messageString;
            TString m_subscribeId;
        };
    }
}
#endif
