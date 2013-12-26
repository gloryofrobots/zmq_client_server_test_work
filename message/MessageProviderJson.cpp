#include "MessageProviderJson.h"
#include "json.h"
#include "types.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>
using namespace boost::posix_time;
namespace dmsg 
{
    ///////////////////////////////////////////////////////////////////
    void MessageProviderJson::serializeMessage(Message &message, TString& dest)
    {
        ptime utc_time = ptime_from_tm(message.utc);
        json::object obj;
        obj.insert("id", message.id);
        obj.insert("utc", to_iso_string(utc_time));
        dest = json::serialize(obj);
    }
    ///////////////////////////////////////////////////////////////////
    void MessageProviderJson::deserializeMessage(Message & message, const TString& source)
    {
        json::value obj = json::parse(source);
        message.id = to_string(obj["id"]);
        TString date = to_string(obj["utc"]);
        ptime utc_time = from_iso_string(date);
        message.utc = to_tm(utc_time);
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
