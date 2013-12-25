#ifndef MESSAGE_PROVIDER_H
#define MESSAGE_PROVIDER_H
#include "Message.h"
namespace dmsg 
{
    class MessageProvider
    {
    public:
        virtual void fillMessage(Message & message) = 0;
        virtual void serializeMessage(const Message & message, TString& dest) = 0;
        virtual void deserializeMessage(Message & message, const TString& source) = 0;
    };
}
#endif
