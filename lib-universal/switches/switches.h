#ifndef SWITCHES_H
#define SWITCHES_H

#include <pstd.h>
#include <arduino-compat.h>

#ifdef ARDUINO
#include "CD74HC4067.h"
#endif

namespace switches
{

class SignalReader
{
public:
    virtual int read(int channel) = 0;
};

class SignalWriter
{
public:
    virtual void write(int address, int state) = 0;
};

#ifdef ARDUINO

struct CD74HC4067Config
{
public:
    int s0;
    int s1;
    int s2;
    int s3;
    int sig;
    int en;

    CD74HC4067Config(){}

    CD74HC4067Config(
        int s0,
        int s1,
        int s2,
        int s3,
        int sig,
        int en)
    {
        this->s0 = s0;
        this->s1 = s1;
        this->s2 = s2;
        this->s3 = s3;
        this->sig = sig;
        this->en = en;
    }
};

class CD74HC4067SignalReader : public SignalReader
{
private:
    CD74HC4067Config cfg;
    CD74HC4067 *mux;

public:
    CD74HC4067SignalReader(CD74HC4067Config cfg);
    void init();
    int read(int channel);
};

#endif

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
    pstd::vector<int> targetAddresses;
    SwitchStatus *status;

    SwitchRoute() {}

    SwitchRoute(SwitchStatus *s, pstd::vector<int> targetAddresses) : SwitchRoute()
    {
        status = s;
        this->targetAddresses = targetAddresses;
    }
};

} // namespace switches

#endif