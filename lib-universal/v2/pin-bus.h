#ifndef V2_PIN_BUS_H
#define V2_PIN_BUS_H

#include <arduino-compat.h>
#include <stdint.h>

namespace v2
{

class PinBus
{

private:
    uint8_t *busState;
    uint8_t busSize;

protected:
    const uint8_t getBusSize();
    void setStateByte(const uint8_t byteIndex, const uint8_t state);
    const uint8_t getStateByte(const uint8_t byteIndex);

public:
    PinBus(const uint8_t busSize);
    ~PinBus();
    const uint8_t getPin(const uint8_t byteIndex, const uint8_t bit) const;
    const void setPin(const uint8_t byteIndex, const uint8_t bit, uint8_t state);

    // Read bus state from underlying implementation (e.g hardware)
    // and initialize internal state
    virtual void readState() = 0;

    // Write current state to underlying implementation (e.g hardware)
    virtual void writeState() = 0;
};

} // namespace v2

#endif