#include <Timers.h>
#include "mocks/FakeTimers.h"
#include <gtest/gtest.h>
// #include <arduino-compat.h>
#include <stdio.h>
#include <random>
#include "logger.h"
#include "test-lib/random.h"
#include <switch-service-v2.h>

namespace
{

class V2SwitchServiceTest : public ::testing::Test
{
protected:
    unsigned int nowMillis;
    int minSignalDurationMs;
    int minIterations;

    FakeTimers fakeTimers;
    v2::SwitchServiceConfig cfg;
    v2::SwitchService *svc;

    virtual v2::SwitchService* createSwitchService(v2::SwitchServiceConfig cfg) = 0;

    void SetUp() override
    {
        this->nowMillis = test::randomNumber(100, 600);
        this->minSignalDurationMs = test::randomNumber(100, 600);
        this->minIterations = test::randomNumber(5, 10);

        logger_log("Setup config: minIterations=%d, minSignalDurationMs=%d, initialNow=%d", 
            minIterations,
            minSignalDurationMs,
            nowMillis
        );

        fakeTimers.setMillis(this->nowMillis);

        this->cfg = v2::SwitchServiceConfig(
            minSignalDurationMs,
            minIterations,
            &fakeTimers);

        this->svc = createSwitchService(cfg);
    }
};

class V2PushButtonSwitchServiceTest : public V2SwitchServiceTest
{
    v2::SwitchService* createSwitchService(v2::SwitchServiceConfig cfg)
    {
        return new v2::PushButtonSwitchService(cfg);
    }
};

class V2ToggleButtonSwitchServiceTest : public V2SwitchServiceTest
{
    v2::SwitchService* createSwitchService(v2::SwitchServiceConfig cfg)
    {
        return new v2::ToggleButtonSwitchService(cfg);
    }
};

TEST_F(V2PushButtonSwitchServiceTest, ChangeStateHighWhenSeenSignalEnough)
{
    v2::Switch status;

    int durationIncrease = minSignalDurationMs / minIterations;

    for (int i = 0; i < minIterations; i++)
    {
        svc->processSignal(HIGH, &status);
        EXPECT_FALSE(status.stateChanged) << "Should not have changed state";
        EXPECT_EQ(status.state, LOW) << "Should not have toggled state";
        EXPECT_EQ(status.seenSignalSince, nowMillis) << "Should remember first time seen signal";
        EXPECT_EQ(status.seenSignalTimes, i + 1) << "Should increment seen times";
        fakeTimers.advance(durationIncrease);
    }

    logger_log("TEST: Completed minIterations stage");

    fakeTimers.advance(durationIncrease);
    svc->processSignal(HIGH, &status);
    EXPECT_TRUE(status.stateChanged) << "Should have changed state";
    EXPECT_EQ(status.state, HIGH) << "Should have HIGH value";
    EXPECT_EQ(status.seenSignalTimes, minIterations + 1) << "Should increment seen times";
    EXPECT_EQ(status.seenSignalSince, nowMillis) << "Should remember first time seen signal";
}

TEST_F(V2PushButtonSwitchServiceTest, DoesntChangeIfContinuingSeeingTheSignal)
{
    v2::Switch status;

    int durationIncrease = minSignalDurationMs / minIterations;

    for (int i = 0; i <= minIterations + 1; i++)
    {
        svc->processSignal(HIGH, &status);
        fakeTimers.advance(durationIncrease);
    }
    EXPECT_EQ(status.state, HIGH) << "Should have HIGH value";

    for (int i = 0; i < minIterations * 3; i++)
    {
        svc->processSignal(HIGH, &status);
        fakeTimers.advance(durationIncrease);
        EXPECT_EQ(status.state, HIGH) << "Should stay HIGH after change";
    }
}

TEST_F(V2PushButtonSwitchServiceTest, ChangeStateLowWhenSeenSignalEnough)
{
    v2::Switch status(HIGH, false, 0, 0);

    int durationIncrease = minSignalDurationMs / minIterations;

    for (int i = 0; i < minIterations; i++)
    {
        svc->processSignal(HIGH, &status);
        EXPECT_FALSE(status.stateChanged) << "Should not have changed state";
        EXPECT_EQ(status.state, HIGH) << "Should not have toggled state";
        EXPECT_EQ(status.seenSignalSince, nowMillis) << "Should remember first time seen signal";
        EXPECT_EQ(status.seenSignalTimes, i + 1) << "Should increment seen times";
        fakeTimers.advance(durationIncrease);
    }

    logger_log("TEST: Completed minIterations stage");

    fakeTimers.advance(durationIncrease);
    svc->processSignal(HIGH, &status);
    EXPECT_TRUE(status.stateChanged) << "Should have changed state";
    EXPECT_EQ(status.state, LOW) << "Should have HIGH value";
    EXPECT_EQ(status.seenSignalTimes, minIterations + 1) << "Should increment seen times";
    EXPECT_EQ(status.seenSignalSince, nowMillis) << "Should remember first time seen signal";
}

TEST_F(V2PushButtonSwitchServiceTest, DoesntChangeStateOnLow)
{
    const int seenSignalTimes = test::randomNumber(100, 600);
    const unsigned int seenSignalSince = test::randomNumber(100, 600);
    v2::Switch status(HIGH, false, seenSignalTimes, seenSignalSince);

    int durationIncrease = minSignalDurationMs / minIterations;

    for (int i = 0; i < minIterations * 3; i++)
    {
        svc->processSignal(LOW, &status);
        EXPECT_FALSE(status.stateChanged) << "Should not have changed state";
        EXPECT_EQ(status.state, HIGH) << "Should not have toggled state";
        fakeTimers.advance(durationIncrease);
    }
}

TEST_F(V2PushButtonSwitchServiceTest, ResetChangeDetectionOnLow)
{
    const int seenSignalTimes = test::randomNumber(100, 600);
    const unsigned int seenSignalSince = test::randomNumber(100, 600);
    v2::Switch status(HIGH, true, seenSignalTimes, seenSignalSince);

    int durationIncrease = minSignalDurationMs / minIterations;

    for (int i = 0; i < minIterations * 3; i++)
    {
        svc->processSignal(LOW, &status);
        EXPECT_FALSE(status.stateChanged) << "Should reset stateChanged flag";
        EXPECT_EQ(status.state, HIGH) << "Should keep currentState";
        EXPECT_EQ(status.seenSignalTimes, 0) << "Should reset seen signal times";
        EXPECT_EQ(status.seenSignalSince, 0) << "Should reset seen signal since";
        fakeTimers.advance(durationIncrease);
    }
}

TEST_F(V2ToggleButtonSwitchServiceTest, ChangeStateFromLowToHighWhenSeenHighSignalEnough)
{
    v2::Switch status;

    int durationIncrease = minSignalDurationMs / minIterations;

    for (int i = 0; i < minIterations; i++)
    {
        svc->processSignal(HIGH, &status);
        EXPECT_FALSE(status.stateChanged) << "Should not have changed state";
        EXPECT_EQ(status.state, LOW) << "Should not have toggled state";
        EXPECT_EQ(status.seenSignalSince, nowMillis) << "Should remember first time seen signal";
        EXPECT_EQ(status.seenSignalTimes, i + 1) << "Should increment seen times";
        fakeTimers.advance(durationIncrease);
    }

    logger_log("TEST: Completed minIterations stage");

    fakeTimers.advance(durationIncrease);
    svc->processSignal(HIGH, &status);
    EXPECT_TRUE(status.stateChanged) << "Should have changed state";
    EXPECT_EQ(status.state, HIGH) << "Should have HIGH value";
    EXPECT_EQ(status.seenSignalTimes, minIterations + 1) << "Should increment seen times";
    EXPECT_EQ(status.seenSignalSince, nowMillis) << "Should remember first time seen signal";
}

TEST_F(V2ToggleButtonSwitchServiceTest, KeepExistingState)
{
    v2::Switch status;

    status.state = test::randomNumber(0, 1);

    int durationIncrease = minSignalDurationMs / minIterations;

    for (int i = 0; i < minIterations * 3; i++)
    {
        svc->processSignal(status.state, &status);
        EXPECT_FALSE(status.stateChanged) << "Should not have changed state";
        EXPECT_EQ(status.state, status.state) << "Should not have toggled state";
        fakeTimers.advance(durationIncrease);
    }
}

TEST_F(V2ToggleButtonSwitchServiceTest, ChangeStateFromHighToLowWhenSeenLowSignalEnough)
{
    v2::Switch status;
    status.state = HIGH;
    status.pendingState = HIGH;

    int durationIncrease = minSignalDurationMs / minIterations;

    for (int i = 0; i < minIterations; i++)
    {
        svc->processSignal(LOW, &status);
        EXPECT_FALSE(status.stateChanged) << "Should not have changed state";
        EXPECT_EQ(status.state, HIGH) << "Should not have toggled state";
        EXPECT_EQ(status.seenSignalSince, nowMillis) << "Should remember first time seen signal";
        EXPECT_EQ(status.seenSignalTimes, i + 1) << "Should increment seen times";
        fakeTimers.advance(durationIncrease);
    }

    logger_log("TEST: Completed minIterations stage");

    fakeTimers.advance(durationIncrease);
    svc->processSignal(LOW, &status);
    EXPECT_TRUE(status.stateChanged) << "Should have changed state";
    EXPECT_EQ(status.state, LOW) << "Should have HIGH value";
    EXPECT_EQ(status.seenSignalTimes, minIterations + 1) << "Should increment seen times";
    EXPECT_EQ(status.seenSignalSince, nowMillis) << "Should remember first time seen signal";
}

TEST_F(V2ToggleButtonSwitchServiceTest, applyStateChangeShouldReset)
{
    v2::Switch status;

    status.state = HIGH;
    status.stateChanged = true;
    status.seenSignalTimes = test::randomNumber(100, 600);
    status.seenSignalSince = test::randomNumber(100, 600);

    svc->applyStateChange(&status);

    EXPECT_FALSE(status.stateChanged) << "Should have reset the state";
    EXPECT_EQ(0, status.seenSignalTimes) << "Should have reset seenSignalTimes";
    EXPECT_EQ(0, status.seenSignalSince) << "Should have reset seenSignalSince";
}

} // namespace
