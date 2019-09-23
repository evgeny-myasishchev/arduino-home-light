#include <pin-bus.h>

namespace v2
{

#ifdef PIN_BUS_VERBOSE
#define pin_bus_log logger_log
#else
#define pin_bus_log
#endif

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

PCF8574Bus::PCF8574Bus(const byte outputBoardsNum, const byte inputBoardsNum)
    : outputBoardsNum(outputBoardsNum), inputBoardsNum(inputBoardsNum), PinBus(outputBoardsNum + inputBoardsNum)
{
    const auto busSize = this->getBusSize();
    byte initialAddress = PCF8574_BASE_ADDR;
    boards = new PCF8574 *[busSize];
    for (size_t i = 0; i < busSize; i++)
    {
        const auto boardAddr = initialAddress++;
        boards[i] = new PCF8574(boardAddr);
    }
}

PCF8574Bus::~PCF8574Bus()
{
    delete boards;
}

void PCF8574Bus::setup(const byte initialState)
{
    for (size_t i = 0; i < this->getBusSize(); i++)
    {
        boards[i]->begin();
    }
    pin_bus_log("Initializing %d bus boards. Initial state: %d", this->getBusSize(), initialState);
}

void PCF8574Bus::readState() 
{
    // Reading only from input boards
    for (size_t i = outputBoardsNum; i < this->getBusSize(); i++)
    {
        const auto byteValue = boards[i]->read8();
        this->setStateByte(i, byteValue);
        pin_bus_log("Loaded board byte: %d, value: %b", i, byteValue);
    }
}

void PCF8574Bus::writeState() 
{
    // Write only to outputs
    for (size_t i = 0; i < outputBoardsNum; i++)
    {
        boards[i]->write8(this->getStateByte(i));
    }
}

#endif

} // namespace v2