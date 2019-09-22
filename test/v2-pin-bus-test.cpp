#include <gtest/gtest.h>
#include <arduino-compat.h>
#include "test-lib/random.h"
#include <pin-bus.h>

namespace
{

class TestPinBus : public v2::PinBus
{

public:
    byte *pendingTestState;

    TestPinBus(const byte busSize) : PinBus(busSize)
    {
    }

    void readState()
    {
        for (size_t i = 0; i < this->getBusSize(); i++)
        {
            this->setStateByte(i, pendingTestState[i]);
        }
    }

    void writeState()
    {
        for (size_t i = 0; i < this->getBusSize(); i++)
        {
            pendingTestState[i] = this->getStateByte(i);
        }
    }
};

TEST(V2PinBus, initialState)
{
    const byte maxBytes = test::randomNumber(5, 10);
    const TestPinBus bus(maxBytes);
    for (size_t byteIndex = 0; byteIndex < maxBytes; byteIndex++)
    {
        const auto pin = bus.getPin(byteIndex, 0);
        EXPECT_EQ(LOW, pin);
    }
}

TEST(V2PinBus, getPin)
{
    const byte maxBytes = test::randomNumber(5, 10);
    byte *state = new byte[maxBytes]();
    for (size_t byteIndex = 0; byteIndex < maxBytes; byteIndex++)
    {
        state[byteIndex] = test::randomNumber(0, 255);
    }

    TestPinBus bus(maxBytes);
    bus.pendingTestState = state;
    bus.readState();
    for (size_t byteIndex = 0; byteIndex < maxBytes; byteIndex++)
    {
        for (size_t bit = 0; bit < 8; bit++)
        {
            const auto pin = bus.getPin(byteIndex, bit);
            EXPECT_EQ(bitRead(state[byteIndex], bit), pin);
        }
    }
}

TEST(V2PinBus, setPin)
{
    const byte maxBytes = test::randomNumber(5, 10);
    byte *state = new byte[maxBytes]();
    TestPinBus bus(maxBytes);
    bus.pendingTestState = state;
    bus.readState();

    byte *randomState = new byte[maxBytes]();
    for (size_t byteIndex = 0; byteIndex < maxBytes; byteIndex++)
    {
        const auto byteVal = test::randomNumber(0, 255);
        randomState[byteIndex] = byteVal;
        for (size_t bit = 0; bit < 8; bit++)
        {
            bus.setPin(byteIndex, bit, bitRead(byteVal, bit));
        }
    }

    bus.writeState();

    for (size_t byteIndex = 0; byteIndex < maxBytes; byteIndex++)
    {
        EXPECT_EQ(state[byteIndex], randomState[byteIndex]);
    }
}

} // namespace
