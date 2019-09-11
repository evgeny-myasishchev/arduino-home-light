namespace v2
{

#ifndef V2_PIN_BUS_H
#define V2_PIN_BUS_H

#include <stdint.h>

class PinBus
{

private:
    uint8_t *switchesState;
    uint8_t *relaysState;

protected:
    // switchesStateSize - size of switches state in bytes
    // relaysStateSize - size of relays state in bytes
    PinBus(
        const uint8_t switchesStateSize,
        const uint8_t relaysStateSize);

    void setSwitchState(const uint8_t byteIndex, const uint8_t state);
    void setRelayState(const uint8_t byteIndex, const uint8_t state);

public:
    virtual void readState() = 0;
    virtual void writeState() = 0;

    const uint8_t getSwitchPin(const uint8_t channel);
    const uint8_t getRelayPin(const uint8_t channel);
    void setRelayPin(const uint8_t channel, const uint8_t state);
};

#ifdef ARDUINO

#include <PCF8574.h>

class PCF8574PinBus : public PinBus
{
private:
    uint8_t readerStartAddr;
    uint8_t readerBoardsNum;
    uint8_t writerStartAddr;
    uint8_t writerBoardsNum;
    PCF8574 **readerBoards;
    PCF8574 **writerBoards;

public:
    PCF8574PinBus(
        const uint8_t readerStartAddr,
        const uint8_t readerBoardsNum,
        const uint8_t writerStartAddr,
        const uint8_t writerBoardsNum);

    void init();

    void fetchState() = 0;
    uint8_t readPin(uint8_t channel);
    uint8_t writePin(uint8_t channel, uint8_t state);
    void commitState() = 0;
};

#endif

} // namespace v2

#endif