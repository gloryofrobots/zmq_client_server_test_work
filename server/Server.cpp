#include "Server.h"
#include "UUIDBoost.h"
#include <ctime>
#include <string.h>

namespace dmsg 
{
    namespace dserver 
    {         
        /////////////////////////////////////////////////////
        Server::Server(MessageProvider * messageProvider, const TString& subscribeId)
            : m_isRun(false)
            , m_messageProvider(messageProvider)
            , m_subscribeId(subscribeId)
        {
            m_uuid = new UUIDBoost();
            m_message.id = m_uuid->toCharArray();
        }
        /////////////////////////////////////////////////////
        Server::~Server()
        {
            delete m_uuid;
        }
        /////////////////////////////////////////////////////
        bool Server::init(TUInt port)
        {
            return this->_onInit(port);
        }
        /////////////////////////////////////////////////////
        bool Server::run(TUInt port)
        {
            if (m_isRun == true)
            {
                return false;
            }
            
            if (this->init(port) == false)
            {
                return false;
            }
            
            while (true)
            {
                bool isSuccess = update();
                if(isSuccess == false)
                {
                    return false;
                }
            }
        }
        /////////////////////////////////////////////////////
        bool Server::update()
        {
            return this->_onUpdate();
        }
        /////////////////////////////////////////////////////
        TRawConstString Server::getUUIDString()
        {
        }
        /////////////////////////////////////////////////////
        const TString &Server::createNewMessageString()
        {
            time_t now = time(0);
            tm* utc = gmtime(&now);
            memcpy((void *)&m_message.utc, (void *)utc, sizeof(tm));
            
            m_messageProvider->serializeMessage(m_message, m_messageString);
            return m_messageString;
        }
        
        const TString &Server::getSubscribeId()
        {
            return m_subscribeId;
        }
        /////////////////////////////////////////////////////
    }
}
