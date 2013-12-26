#include "TimerBoost.h"

using namespace boost::posix_time;

namespace dmsg 
{
    //////////////////////////////////////////////////////////////
    void TimerBoost::start()
    {
        m_startTime = boost::posix_time::second_clock::local_time();
    }
    //////////////////////////////////////////////////////////////
    long TimerBoost::stop()
    {
        m_stopTime = boost::posix_time::second_clock::local_time();
        time_duration diff = m_stopTime - m_startTime;
        long milliseconds = diff.total_milliseconds();
        return milliseconds;
    }   
    //////////////////////////////////////////////////////////////
}
