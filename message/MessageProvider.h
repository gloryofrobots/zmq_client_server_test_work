#ifndef MESSAGE_PROVIDER_H
#define MESSAGE_PROVIDER_H
#include "Message.h"
namespace dmsg 
{
    class MessageProvider
    {
    public:
        virtual bool serializeMessage(Message & message, TString& dest) = 0;
        virtual bool deserializeMessage(Message & message, const TString& source) = 0;
    };
    
}
#endif
