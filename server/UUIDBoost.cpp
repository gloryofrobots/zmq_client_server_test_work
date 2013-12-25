#include "UUIDBoost.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <sstream>
namespace dmsg 
{
    namespace dserver
    {
        ////////////////////////////////////////////////////////////
        UUIDBoost::UUIDBoost()
        {
            boost::uuids::uuid uuid = boost::uuids::uuid(boost::uuids::random_generator()());
            std::stringstream ss;
            ss << uuid;
            m_stringValue = ss.str();
        }
        ////////////////////////////////////////////////////////////
        UUIDBoost::~UUIDBoost()
        {
        }
        ////////////////////////////////////////////////////////////
        TRawConstString UUIDBoost::toCharArray()
        {
            return m_stringValue.c_str();
        }
        ////////////////////////////////////////////////////////////
    }
}
