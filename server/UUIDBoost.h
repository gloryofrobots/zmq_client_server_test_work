#ifndef UUIDBoost_H
#define UUIDBoost_H
#include "UUID.h"
#include <string>
namespace dmsg 
{
    namespace dserver
    {
        class UUIDBoost : public UUID
        {
        public:
            UUIDBoost();
            ~UUIDBoost();
            virtual TRawConstString toCharArray();
            
        private:
            std::string m_stringValue;
        };
        
    }
}
#endif
