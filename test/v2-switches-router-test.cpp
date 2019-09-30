#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <arduino-compat.h>
#include <stdio.h>
#include "test-lib/random.h"
#include <switches-router-v2.h>
#include "test-lib/test-pin-bus.h"

namespace
{

using namespace v2;

class MockSwitchService : public SwitchService
{
public:
    MockSwitchService() : SwitchService(SwitchServiceConfig{}) {}
    MOCK_METHOD(void, processSignal, (uint8_t signal, Switch *sw));
    MOCK_METHOD(void, applyStateChange, (Switch * sw));
};

class V2SwitchesRouterTest : public ::testing::Test
{
public:
    TestPinBus *bus;
    SwitchesRouter *router;
    testing::NiceMock<MockSwitchService> *pushBtnSwitchSvc;
    testing::NiceMock<MockSwitchService> *toggleBtnSwitchSvc;

protected:
    void SetUp() override
    {
        bus = new TestPinBus(2);
        bus->pendingTestState = new byte[2]();
        pushBtnSwitchSvc = new testing::NiceMock<MockSwitchService>();
        toggleBtnSwitchSvc = new testing::NiceMock<MockSwitchService>();
        SwitchRouterServices services{
            .bus = bus,
            .pushBtnSwitchSvc = pushBtnSwitchSvc,
            .toggleBtnSwitchSvc = toggleBtnSwitchSvc,
        };
        router = new SwitchesRouter(services);
    }
    void TearDown() override
    {
        delete bus->pendingTestState;
        delete bus;
        delete router;
        delete toggleBtnSwitchSvc;
        delete pushBtnSwitchSvc;
    }
};

TEST_F(V2SwitchesRouterTest, processRoutesNoChanges)
{
    const byte state = test::randomNumber(0, 255);
    bus->pendingTestState[0] = state;
    bus->readState();

    Switch route1{.switchAddress = 0};
    Switch route2{.switchAddress = 1};
    Switch route3{.switchAddress = 2, .type = SwitchType::Toggle};
    Switch route4{.switchAddress = 3};
    Switch route5{.switchAddress = 4, .type = SwitchType::Toggle};
    Switch *routesArray[] = {&route4, &route2, &route3, &route1, &route5};
    ArrayPtr<Switch *> routes(5, (Switch **)&routesArray);

    EXPECT_CALL((*pushBtnSwitchSvc), processSignal(bitRead(state, route1.switchAddress), &route1));
    EXPECT_CALL((*pushBtnSwitchSvc), processSignal(bitRead(state, route2.switchAddress), &route2));
    EXPECT_CALL((*toggleBtnSwitchSvc), processSignal(bitRead(state, route3.switchAddress), &route3));
    EXPECT_CALL((*pushBtnSwitchSvc), processSignal(bitRead(state, route4.switchAddress), &route4));
    EXPECT_CALL((*toggleBtnSwitchSvc), processSignal(bitRead(state, route5.switchAddress), &route5));

    router->processRoutes(routes);
}

} // namespace
