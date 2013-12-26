#ifndef TIMER_H
#define TIMER_H
namespace dmsg 
{
    class Timer
    {
    public:
        virtual void start() = 0;
        virtual long stop() = 0;
    };
    
}
#endif
