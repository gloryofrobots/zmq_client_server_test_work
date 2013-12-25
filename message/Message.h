#ifndef MESSAGE_H
#define MESSAGE_H
#include "types.h"
#include <ctime>
namespace dmsg 
{
    struct Message
    {
        tm utc;
        TString id;
    };
}
#endif
