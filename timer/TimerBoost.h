#ifndef TIMER_BOOST_H
#define TIMER_BOOST_H
#include "Timer.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <ctime>
namespace dmsg 
{
    
    class TimerBoost : public Timer
    {
    public:
        virtual void start();
        virtual long stop();
    private:
        boost::posix_time::ptime m_startTime;
        boost::posix_time::ptime m_stopTime;
        time_t m_start;
        time_t m_stop;
    };
}
#endif
