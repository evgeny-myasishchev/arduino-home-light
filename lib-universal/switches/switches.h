#ifndef SWITCHES_H
#define SWITCHES_H

#include <pstd.h>
#include <arduino-compat.h>
#include <Timers.h>
#include <logger.h>

#ifdef ARDUINO
#include <PCF8574.h>
#endif

namespace switches
{

class SignalReader
{
public:
    // TODO: Refactor to use uint8_t
    virtual int read(int channel) = 0;
};

class SignalWriter
{
public:
    virtual void write(int address, int state) = 0;
};

#ifdef ARDUINO

class PCF8574IO : public SignalReader, public SignalWriter
{
private:
    uint8_t readerStartAddr;
    uint8_t readerBoardsNum;
    uint8_t writerStartAddr;
    uint8_t writerBoardsNum;
    PCF8574 **readerBoards;
    PCF8574 **writerBoards;

public:
    PCF8574IO(
        const uint8_t readerStartAddr,
        const uint8_t readerBoardsNum,
        const uint8_t writerStartAddr,
        const uint8_t writerBoardsNum);

    void init();
    int read(int channel);
    void write(int address, int state);
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
    pstd::vector<int> *targetAddresses;
    SwitchStatus *status;

    SwitchRoute() {}

    SwitchRoute(SwitchStatus *s, pstd::vector<int> *targetAddresses) : SwitchRoute()
    {
        status = s;
        this->targetAddresses = targetAddresses;
    }
};

} // namespace switches

#endif