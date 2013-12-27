#include "MessageProviderJson.h"
#include "json.h"
#include "types.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>

using namespace boost::posix_time;
namespace dmsg 
{
    ///////////////////////////////////////////////////////////////////
    bool MessageProviderJson::serializeMessage(Message &message, TString& dest)
    {
        try 
        {
            json::object obj;
            obj.insert("id", message.id);
            obj.insert("utc", message.timestamp);
            dest = json::serialize(obj);
            return true;
        }
        catch(...)
        {
            return false;
        }
    }
    ///////////////////////////////////////////////////////////////////
    bool MessageProviderJson::deserializeMessage(Message & message, const TString& source)
    {
        try 
        {
            json::value obj = json::parse(source);
            message.id = to_string(obj["id"]);
            TString datetime = to_string(obj["utc"]);
            
            message.timestamp = strtoll(datetime.c_str(),0,10);
            return true;
        }
        catch(...)
        {
            return false;
        }
    }
    ///////////////////////////////////////////////////////////////////
    MessageProviderJson::MessageProviderJson()
    {
    }
    ///////////////////////////////////////////////////////////////////
    MessageProviderJson::~MessageProviderJson()
    {
    }
    ///////////////////////////////////////////////////////////////////
}
