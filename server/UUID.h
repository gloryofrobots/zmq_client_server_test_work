#ifndef UUID_H
#define UUID_H
#include "types.h"
namespace dmsg 
{
    namespace dserver
    {
        class UUID
        {
        public:
            virtual TRawConstString toCharArray() = 0;        
        };
    }
}
#endif
