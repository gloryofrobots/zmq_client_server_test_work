#ifndef MESSAGE_PROVIDER_JSON_H
#define MESSAGE_PROVIDER_JSON_H
#include "MessageProvider.h"

namespace dmsg 
{
    class MessageProviderJson : public MessageProvider
    {
    public:
        MessageProviderJson();
        virtual ~MessageProviderJson();
        virtual void serializeMessage(Message & message, TString& dest);
        virtual void deserializeMessage(Message & message, const TString& source);
    private:
        TString m_tempBuffer;
        
    };
}
#endif
