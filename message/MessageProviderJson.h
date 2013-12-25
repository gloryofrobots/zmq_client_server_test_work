#ifndef MESSAGE_PROVIDER_H
#define MESSAGE_PROVIDER_H
#include "MessageProvider.h"
#include "json.h"
#include <boost/date_time/posix_time/posix_time.hpp>

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
