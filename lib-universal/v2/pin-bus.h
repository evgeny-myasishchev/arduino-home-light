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
    void setStateByte(const uint8_t byteIndex, const uint8_t state);
    const uint8_t getStateByte(const uint8_t byteIndex);

public:
    PinBus(const uint8_t busSize);
    ~PinBus();
    const uint8_t getPin(const uint8_t byteIndex, const uint8_t bit) const;
    const void setPin(const uint8_t byteIndex, const uint8_t bit, uint8_t state);

    virtual void readState() = 0;
    virtual void writeState() = 0;
};

} // namespace v2

#endif