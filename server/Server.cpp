#include <ctime>
#include <string.h>

#include "Server.h"
#include "UUIDBoost.h"
#include "LogSystem.h"
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
                DMSG_LOGGER("Can`t initialize server");
                return false;
            }
            
            m_isRun = true;
            while (true)
            {
                bool isSuccess = update();
                if(isSuccess == false)
                {
                    m_isRun = false;
                    return false;
                }
            }
        }
        /////////////////////////////////////////////////////
        bool Server::update()
        {
            if(createNewMessageString() == false)
            {
                return false;
            }   
            
            return this->_onUpdate();
        }
        /////////////////////////////////////////////////////
        TRawConstString Server::getUUIDString()
        {
        }
        /////////////////////////////////////////////////////
        bool Server::createNewMessageString()
        {
            time_t now = time(0);
            tm* utc = gmtime(&now);
            memcpy((void *)&m_message.utc, (void *)utc, sizeof(tm));
            
            if(m_messageProvider->serializeMessage(m_message, m_messageString) == false)
            {
                log("Error during serialization message ");
            } 
        }
        /////////////////////////////////////////////////////
        const TString &Server::getMessageString()
        {
            return m_messageString;
        }
        /////////////////////////////////////////////////////
        const TString &Server::getSubscribeId()
        {
            return m_subscribeId;
        }
        /////////////////////////////////////////////////////
    }
}
