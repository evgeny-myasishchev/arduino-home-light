#include <switches.h>
#include <switch-service.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <arduino-compat.h>
#include <stdio.h>
#include <random>

namespace
{

using namespace switches;

class MockSignalReader : public SignalReader
{
public:
    MOCK_METHOD1(read, void(int channel));
};

class MockSignalWriter : public SignalWriter
{
public:
    MOCK_METHOD2(write, void(int address, int state));
};

class MockSwitchService : public SwitchService
{
public:
    MOCK_METHOD2(processSignal, void(int signal, SwitchStatus *switchStatus));
    MOCK_METHOD1(applyStateChange, void(SwitchStatus *switchStatus));
};

class SwitchesRouterTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
    }
};

TEST_F(SwitchesRouterTest, processRoutes)
{
    MockSignalReader signalReader;
    for (size_t i = 0; i < 2; i++)
    {
        EXPECT_CALL(signalReader, read(i));
    }
    
    signalReader.read(0);
    signalReader.read(1);
}

} // namespace
