#include <switches.h>
#include <switch-service.h>
#include <switches-router.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <arduino-compat.h>
#include <stdio.h>
#include <random>

namespace
{

using namespace switches;
using namespace testing;

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
    MockSwitchService() : SwitchService(SwitchServiceConfig{}) {
    }
    MOCK_METHOD2(processSignal, void(int signal, SwitchStatus *switchStatus));
    MOCK_METHOD1(applyStateChange, void(SwitchStatus *switchStatus));
};

class SwitchesRouterTest : public ::testing::Test
{
protected:
    StrictMock<MockSignalReader> signalReader;
    StrictMock<MockSignalWriter> signalWriter;
    StrictMock<MockSwitchService> switchService;

    SwitchRouterServices services = SwitchRouterServices(&signalReader, &signalWriter, &switchService);

    void SetUp() override
    {
        // services = SwitchRouterServices(&signalReader, &signalWriter, &switchService);
    }
};

void foo(std::initializer_list<int>& l) {

}

TEST_F(SwitchesRouterTest, processRoutes)
{
    // SwitchRoute routeValues[10] = {
    //     SwitchRoute().withTargetAddresses(pstd::vector<int>(int[2]{ 1, 2 }))
    // };
    
    // pstd::vector<SwitchRoute> routes({SwitchRoute()});

    for (size_t i = 0; i < 2; i++)
    {
        EXPECT_CALL(signalReader, read(i));
    }
    
    signalReader.read(0);
    signalReader.read(1);
}

} // namespace
