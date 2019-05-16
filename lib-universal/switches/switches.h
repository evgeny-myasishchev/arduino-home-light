#ifndef SWITCHES_H
#define SWITCHES_H

namespace switches
{

class SignalReader
{
public:
    virtual void read(int channel) = 0;
};

class SignalWriter
{
public:
    virtual void write(int address, int state) = 0;
};

struct SwitchStatus
{
public:
    int currentState = 0;
    bool stateChanged = false;
    int seenSignalTimes = 0;
    unsigned int seenSignalSince = 0;

    SwitchStatus() {}

    SwitchStatus(
        int currentState,
        bool stateChanged,
        int seenSignalTimes,
        unsigned int seenSignalSince)
    {
        this->currentState = currentState;
        this->stateChanged = stateChanged;
        this->currentState = currentState;
        this->seenSignalTimes = seenSignalTimes;
        this->seenSignalSince = seenSignalSince;
    }
};

struct SwitchRoute 
{
public:
    SwitchStatus status;
};

}

#endif