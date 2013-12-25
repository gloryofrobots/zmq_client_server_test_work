#include "MessageProviderJson.h"
#include "json.h"
#include "types.h"
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace boost::posix_time;

namespace dmsg 
{
    ///////////////////////////////////////////////////////////////////
    void MessageProviderJson::fillMessage(Message & message)
    {
        
    }
    ///////////////////////////////////////////////////////////////////
    void MessageProviderJson::serializeMessage(const Message & message, TString& dest)
    {
            TRawConstString uuid = "";
            ptime utc_time = second_clock::universal_time();
            json::object obj;
            obj.insert("id", uuid);
            obj.insert("utc", to_iso_string(utc_time));
            std::string serialized = json::serialize(obj);
            std::cout << serialized << std::endl;
    }
    ///////////////////////////////////////////////////////////////////
    void MessageProviderJson::deserializeMessage(Message & message, const TString& source)
    {
        
    }
    ///////////////////////////////////////////////////////////////////
}
