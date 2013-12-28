#ifndef SUBSCRIBER_ZMQ_H
#define SUBSCRIBER_ZMQ_H
#include "Subscriber.h"
namespace dmsg 
{
    namespace dclient
    {
        class SubscriberZMQ : public Subscriber
        {
        public:
            SubscriberZMQ(MessageProvider * messageProvider, const TString & subscribeId);
            virtual ~SubscriberZMQ();
            
        protected:  
            virtual bool _onInit(TUInt port);
            virtual ERequestStatus _onUpdate();
            virtual bool _onStop();

        private:
            void * m_context;
            void * m_socket;
            void clear();
        };
    }
}
#endif
