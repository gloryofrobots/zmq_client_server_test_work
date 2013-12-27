#ifndef DMSG_MESSAGE_H
#define DMSG_MESSAGE_H
#include "types.h"
#include <ctime>
namespace dmsg 
{
    struct Message
    {
        TTimeStamp timestamp;
        TString id;
    };
}
#endif
