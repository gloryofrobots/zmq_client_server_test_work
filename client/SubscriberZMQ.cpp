#include "SubscriberZMQ.h"
#include "LogSystem.h"
extern "C" 
{
    #include "zmqhelpers.h"
}

#include <iostream>

namespace dmsg
{
    namespace dclient
    {
        static void zmqlog(TRawConstString msg)
        {
            DMSG_LOGGER("%s %s", msg, zmq_strerror(errno));
        }
        ///////////////////////////////////////
        SubscriberZMQ::SubscriberZMQ(MessageProvider * messageProvider, const TString & subscribeId)
            : Subscriber(messageProvider, subscribeId)
            , m_context(0)
            , m_socket(0)
        {
            //init signal handler
            s_catch_signals();
        }
        ///////////////////////////////////////
        SubscriberZMQ::~SubscriberZMQ()
        {
            clear();
        }
        ///////////////////////////////////////
        bool SubscriberZMQ::_onInit(TUInt port)
        {
            m_context = zmq_ctx_new();
            if (m_context == 0)
            {
                zmqlog("Error occurred during zmq_ctx_new()");
                return false;
            } 
            
            m_socket = zmq_socket(m_context, ZMQ_SUB);
            if (m_socket == 0)
            {
                zmqlog("Error occurred during zmq_socket()");
                clear();
                return false;
            } 
            
            TChar address[100] = {'\0'};
            sprintf(address, "tcp://localhost:%u", port);
            int result = zmq_connect(m_socket, address);

            if (result != 0)
            {
                zmqlog("Error occurred during zmq_init()");
                clear();
                return false;
            }
            
            const TString& subscribeId = getSubscribeId();
            result = zmq_setsockopt (m_socket, ZMQ_SUBSCRIBE, subscribeId.c_str(), subscribeId.length() - 1);
            if (result != 0)
            {
                zmqlog("Error occurred during zmq_setsockopt");
                clear();
                return false;
            }
            
            return true;
        }
        ///////////////////////////////////////
        bool SubscriberZMQ::_onUpdate()
        {
            if (s_interrupted)
            {
                return false;
            } 
            
            if (isOnRun() == false)
            {
                return false;
            }
            
            
            startTimer();
           
            TChar *subscribeId = s_recv(m_socket);
            if(subscribeId == NULL)
            {
                zmqlog("Error receiving subscribe id");
                return false;
            }
            
            TChar *contents = s_recv(m_socket);
            if(contents == NULL)
            {
                zmqlog("Error receiving message contents");
                return false;
            }
            
            stopTimer();
            
            TString data = contents;
            
            if (parseMessage(data) == false)
            {
                DMSG_LOGGER("Error parsing message %s", contents);
                //free(subscribeId);
                //free(contents);
                //return false;
            }
            
            //log("%i [%s] %s \n",(int)m_state.pingTime, m_state.message.id.c_str(), contents);
            DMSG_LOGGER(" %s ", contents);
            free(subscribeId);
            free(contents);

            return true;
        }
        ///////////////////////////////////////
        bool SubscriberZMQ::_onStop()
        {
            //clear();
        }
        ///////////////////////////////////////
        void SubscriberZMQ::clear()
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
