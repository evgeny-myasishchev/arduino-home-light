#ifndef SwitchService_h
#define SwitchService_h

#include <Timers.h>

struct SwitchServiceConfig
{
    // Min number of ms a signal should be seen
    // to consider button pressed or switched
    unsigned int minSignalDurationMs;

    // Min number of times we've seen the signal
    // to take it in action
    int minSignalIterations;

    Timers * timers;

    SwitchServiceConfig(): 
        minSignalDurationMs(200), 
        minSignalIterations(10),
        timers(new Timers())
    {
    }
};

struct SwitchStatus
{
    public:
        int currentState;
        bool stateChanged;
};

struct PushButtonSwitchStatus : SwitchStatus
{
    public:
        int seenSignalTimes;
        int seenSignalSince;
};


class SwitchService
{
protected:
    SwitchServiceConfig cfg;
public:
    SwitchService(SwitchServiceConfig cfg);
    virtual void processSignal(int signal, SwitchStatus &switchStatus) = 0;
};

class PushButtonSwitchService : SwitchService
{
public:
    PushButtonSwitchService(SwitchServiceConfig cfg);
    virtual void processSignal(int signal, PushButtonSwitchStatus &switchStatus) = 0;
};


#endif