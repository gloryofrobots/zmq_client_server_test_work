#ifndef MESSAGE_PROVIDER_JSON_H
#define MESSAGE_PROVIDER_JSON_H
#include "MessageProvider.h"

namespace dmsg 
{
    class MessageProviderJson : public MessageProvider
    {
    public:
        void fillMessage(Message & message);
        void serializeMessage(const Message & message, TString& dest);
        void deserializeMessage(Message & message, const TString& source);
    };
}
#endif
