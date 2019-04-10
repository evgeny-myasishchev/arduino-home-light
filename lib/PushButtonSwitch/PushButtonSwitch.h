#ifndef PushButton_h
#define PushButton_h

#include <timers.h>

struct pushButtonSwitchConfig
{
    // Min number of ms a signal should be seen
    // to consider button pressed or switched
    int minSignalDurationMs;

    // Min number of times we've seen the signal
    // to take it in action
    int minSignalIterations;

    nowMillisProc nowMillis;

    pushButtonSwitchConfig(): 
        minSignalDurationMs(200), 
        minSignalIterations(10), 
        nowMillis(defaultNowMillisProc())
    {
    }
};

class PushButtonSwitch
{
private:
    /* data */
public:
    PushButtonSwitch(pushButtonSwitchConfig cfg);

    // Return state of a button (either LOW or HIGH)
    int getState();

    // Indicates wether state change recognised
    bool hasStateChanged();

    // 
    void processCurrentLevel(int level);

    // Make current state active
    void applyCurrentState();
};

#endif