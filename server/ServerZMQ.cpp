#include "ServerZMQ.h"
#include "LogSystem.h"
extern "C" 
{
#include "zmqhelpers.h"
}
#include <iostream>
namespace dmsg
{
    namespace dserver
    {
        static void zmqlog(TRawConstString msg)
        {
            DMSG_LOGGER("%s %s",msg, zmq_strerror (errno));
        }
        
        ServerZMQ::ServerZMQ(MessageProvider* messageProvider, const TString &subscribeId) 
            : Server(messageProvider, subscribeId)
            , m_context(0)
            , m_socket(0)
        {
        }
        
        ServerZMQ::~ServerZMQ()
        {
            clear();
        }
        
        bool ServerZMQ::_onInit(TUInt port)
        {
            //init zmq
            m_context = zmq_ctx_new();
            if (m_context == 0)
            {
                zmqlog("Error occurred during zmq_ctx_new()");
                return false;
            } 
            
            m_socket = zmq_socket(m_context, ZMQ_PUB);
            if (m_socket == 0)
            {
                zmqlog("Error occurred during zmq_socket()");
                clear();
                return false;
            } 
            
            //bind to chosen port
            TChar address[100] = {'\0'};
            sprintf(address, "tcp://*:%u", port);
            int result = zmq_bind(m_socket, address);
            if (result != 0)
            {
                zmqlog("Error occurred during zmq_bind()");
                clear();
                return false;
            }
            
            //init signal handler
            s_catch_signals();
            return true;
        }
        
        bool ServerZMQ::_onUpdate()
        {
            if (s_interrupted)
            {
                return false;
            } 
            
            int result;
            const TString& subscriberId = this->getSubscribeId();
            result = s_sendmore(m_socket, subscriberId.c_str());
            if (result == -1)
            {
                DMSG_LOGGER("Error occurred during send subscribe id");
            }
            
            const TString& message = getMessageString();
            DMSG_LOGGER(message.c_str());
            
            result = s_send_const(m_socket, message.c_str());
            if (result == -1)
            {
                zmqlog("Error occurred during send message ");
                DMSG_LOGGER("Error sending %s ", message.c_str());
            }
            
            s_sleep(1000);
            return true;
        }
        
        void ServerZMQ::clear()
        {
            if (m_socket != 0)
            {   
                zmq_close(m_socket);
                m_socket = 0;
            }
            
            if (m_context != 0)
            {
                zmq_ctx_destroy(m_context);
                m_context = 0;
            }
        }
    }
}
