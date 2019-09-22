#ifndef V2_PIN_BUS_H
#define V2_PIN_BUS_H

#include <arduino-compat.h>

namespace v2
{

class PinBus
{

private:
    byte *busState;
    byte busSize;

protected:
    const byte getBusSize();
    void setStateByte(const byte byteIndex, const byte state);
    const byte getStateByte(const byte byteIndex);

public:
    PinBus(const byte busSize);
    ~PinBus();
    const byte getPin(const byte byteIndex, const byte bit) const;
    const void setPin(const byte byteIndex, const byte bit, byte state);

    // Read bus state from underlying implementation (e.g hardware)
    // and initialize internal state
    virtual void readState() = 0;

    // Write current state to underlying implementation (e.g hardware)
    virtual void writeState() = 0;
};

#ifdef ARDUINO

#include <PCF8574.h>

#define PCF8574_BASE_ADDR 0x20

class PCF8574Bus : public PinBus
{
private:
    PCF8574 **boards;
public:
    PCF8574Bus(const byte busSize);
    ~PCF8574Bus();

    void setup();

    void readState();
    void writeState();
};

#endif

} // namespace v2

#endif