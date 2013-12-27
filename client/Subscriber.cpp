#include "Subscriber.h"
#include <algorithm>
#include "TimerBoost.h"
namespace dmsg 
{
    namespace dclient 
    {         
        /////////////////////////////////////////////////////
        Subscriber::Subscriber(MessageProvider * messageProvider, const TString& subscribeId)
            : m_isRun(false)
            , m_messageProvider(messageProvider)
            , m_subscribeId(subscribeId)
        {
            m_timer = new TimerBoost();
            m_state.status = OFFLINE;
        }
        /////////////////////////////////////////////////////
        Subscriber::~Subscriber()
        {
            delete m_timer;
        }
        /////////////////////////////////////////////////////
        //add listener and notify it
        void Subscriber::addListener(Subscriber::SubscribeListener * listener)
        {
            if( std::find(m_listeners.begin(), m_listeners.end(), listener) != m_listeners.end())
            {
                return;
            }
            
            listener->update(m_state);
            
            m_listeners.push_back(listener);
        }
        /////////////////////////////////////////////////////
        void Subscriber::removeListener(Subscriber::SubscribeListener *listener)
        {
            TVectorListeners::iterator  it = std::find(m_listeners.begin(), m_listeners.end(), listener);
            if(it == m_listeners.end())
            {
                return;
            }
            
            m_listeners.erase(it);
        }
        /////////////////////////////////////////////////////
        bool Subscriber::init(TUInt port)
        {
            return this->_onInit(port);
        }
        /////////////////////////////////////////////////////
        bool Subscriber::run(TUInt port)
        {
            if (m_isRun == true)
            {
                return false;
            }
            
            if (this->init(port) == false)
            {
                return false;
            }
            
            m_state.status = ONLINE;
            
            m_isRun = true;
            while (true)
            {
                bool isSuccess = update();
                if(isSuccess == false)
                {
                    m_state.status = OFFLINE;
                    stop();
                    return false;
                }
                
                m_state.status = ONLINE;
                notifyListenersForUpdate();
            }
        }
        /////////////////////////////////////////////////////
        void Subscriber::stop()
        {
            m_isRun = false;
            this->_onStop();
        }
        /////////////////////////////////////////////////////
        bool Subscriber::isOnRun()
        {
            return m_isRun;
        }
        /////////////////////////////////////////////////////
        void Subscriber::startTimer()
        {
            m_timer->start();
        }
        /////////////////////////////////////////////////////
        void Subscriber::stopTimer()
        {
            m_state.pingTime = m_timer->stop();
        }
        /////////////////////////////////////////////////////
        bool Subscriber::update()
        {
            if (m_isRun == false)
            {
                return false;
            }
            
            return this->_onUpdate();
        }
        /////////////////////////////////////////////////////
        void Subscriber::notifyListenersForUpdate()
        {
            for( TVectorListeners::iterator 
                 it = m_listeners.begin(), 
                 it_end = m_listeners.end();
                 it != it_end;
                 ++it )
            {
                (*it)->update(m_state);
            }
        }
        /////////////////////////////////////////////////////
        const TString &Subscriber::getSubscribeId()
        {
            return m_subscribeId;
        }
        /////////////////////////////////////////////////////
        bool Subscriber::parseMessage(const TString & messageString)
        {
            return m_messageProvider->deserializeMessage(m_state.message, messageString);
        }
        /////////////////////////////////////////////////////
    }
}
