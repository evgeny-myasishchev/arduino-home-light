#include <pin-bus.h>

namespace v2
{

PinBus::PinBus(const byte busSize)
{
    this->busSize = busSize;
    this->busState = new byte[busSize]();
}

PinBus::~PinBus()
{
    delete this->busState;
}

const byte PinBus::getBusSize()
{
    return busSize;
}

void PinBus::setStateByte(const byte byteIndex, const byte state)
{
    if (byteIndex >= this->busSize)
    {
        return;
    }
    this->busState[byteIndex] = state;
}

const byte PinBus::getStateByte(const byte byteIndex)
{
    return this->busState[byteIndex];
}

const byte PinBus::getPin(const byte byteIndex, const byte bit) const
{
    if (byteIndex >= this->busSize)
    {
        return LOW;
    }
    const auto byte = this->busState[byteIndex];
    return bitRead(byte, bit);
}

const void PinBus::setPin(const byte byteIndex, const byte bit, byte state)
{
    if (byteIndex >= this->busSize)
    {
        return;
    }
    bitWrite(this->busState[byteIndex], bit, state);
}

#ifdef ARDUINO

PCF8574Bus::PCF8574Bus(const byte busSize) : PinBus(busSize)
{
    byte initialAddress = PCF8574_BASE_ADDR;
    boards = new PCF8574 *[busSize];
    for (size_t i = 0; i < busSize; i++)
    {
        const auto boardAddr = initialAddress++;
        boards[i] = new PCF8574(boardAddr);
    }
}

~PCF8574Bus::PCF8574Bus()
{
    delete boards;
}

void PCF8574Bus::setup()
{
    for (size_t i = 0; i < this->busSize(); i++)
    {
        boards[i]->begin(initialState);
    }
}

void PCF8574Bus::readState() {}

void PCF8574Bus::writeState() {}

#endif

} // namespace v2