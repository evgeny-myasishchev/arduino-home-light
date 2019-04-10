#ifndef fake_timers_h
#define fake_timers_h

#include <Timers.h>

class FakeTimers: public Timers
{
private:
    unsigned long currentMillis;
public:
    void setMillis(unsigned long value);
    void advance(unsigned long step);

    unsigned long millis();
};


#endif