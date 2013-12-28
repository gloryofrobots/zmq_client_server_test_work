#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H
#include "MessageProvider.h"
#include <vector>
namespace dmsg 
{
    class Timer;
    namespace dclient
    {
        class Subscriber
        {
        public:
            enum EStateStatus
            {
                OFFLINE, ONLINE
            };
            
            enum ERequestStatus
            {
                FATAL_ERROR, ERROR, COMPLETE
            };
            
            struct State
            {
                EStateStatus status;
                ERequestStatus requestStatus;
                Message message;
                long pingTime;
            };
            
            class SubscribeListener {
            public:
                virtual void update(const State& state) = 0;                        
            };
            
            Subscriber(MessageProvider * messageProvider, const TString & subscribeId);
            
            //add listener and notify it
            void addListener(SubscribeListener * listener);
            void removeListener(SubscribeListener * listener);
            
            virtual ~Subscriber();
            bool run(TUInt port);
            void stop();
            bool isOnRun();
        protected:  
            virtual bool _onInit(TUInt port) = 0;
            virtual ERequestStatus _onUpdate() = 0;
            virtual bool _onStop() = 0;
            
            void startTimer();
            void stopTimer();
            
            bool parseMessage(const TString& messageString);
            const TString& getSubscribeId(); 
            State m_state;
        private:
            bool init(TUInt port);
            bool update();
            void notifyListenersForUpdate();
            
            bool m_isRun;
            MessageProvider * m_messageProvider;
           
            TString m_subscribeId;
            Timer* m_timer;
            typedef std::vector<SubscribeListener *> TVectorListeners;
            TVectorListeners m_listeners;
        };
    }
}
#endif
