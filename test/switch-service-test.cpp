#include <Timers.h>
#include "mocks/FakeTimers.h"
#include <switch-service.h>
#include <gtest/gtest.h>
#include <arduino-compat.h>
#include <stdio.h>
#include <random>
#include "logger.h"
#include "test-lib/random.h"

namespace
{

class SwitchServiceTest : public ::testing::Test
{
protected:
    unsigned int nowMillis;
    int minSignalDurationMs;
    int minIterations;

    FakeTimers fakeTimers;
    switch_service::SwitchServiceConfig cfg;
    switch_service::SwitchService *svc;

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

        this->cfg = switch_service::SwitchServiceConfig(
            minSignalDurationMs,
            minIterations,
            &fakeTimers);

        this->svc = new switch_service::PushButtonSwitchService(cfg);
    }
};

TEST_F(SwitchServiceTest, ChangeStateHighWhenSeenSignalEnough)
{
    switch_service::SwitchStatus status;

    int durationIncrease = minSignalDurationMs / minIterations;

    for (int i = 0; i < minIterations; i++)
    {
        svc->processSignal(HIGH, &status);
        EXPECT_FALSE(status.stateChanged) << "Should not have changed state";
        EXPECT_EQ(status.currentState, LOW) << "Should not have toggled state";
        EXPECT_EQ(status.seenSignalSince, nowMillis) << "Should remember first time seen signal";
        EXPECT_EQ(status.seenSignalTimes, i + 1) << "Should increment seen times";
        fakeTimers.advance(durationIncrease);
    }

    logger_log("TEST: Completed minIterations stage");

    fakeTimers.advance(durationIncrease);
    svc->processSignal(HIGH, &status);
    EXPECT_TRUE(status.stateChanged) << "Should have changed state";
    EXPECT_EQ(status.currentState, HIGH) << "Should have HIGH value";
    EXPECT_EQ(status.seenSignalTimes, minIterations + 1) << "Should increment seen times";
    EXPECT_EQ(status.seenSignalSince, nowMillis) << "Should remember first time seen signal";
}

TEST_F(SwitchServiceTest, ChangeStateLowWhenSeenSignalEnough)
{
    switch_service::SwitchStatus status(HIGH, false, 0, 0);

    int durationIncrease = minSignalDurationMs / minIterations;

    for (int i = 0; i < minIterations; i++)
    {
        svc->processSignal(HIGH, &status);
        EXPECT_FALSE(status.stateChanged) << "Should not have changed state";
        EXPECT_EQ(status.currentState, HIGH) << "Should not have toggled state";
        EXPECT_EQ(status.seenSignalSince, nowMillis) << "Should remember first time seen signal";
        EXPECT_EQ(status.seenSignalTimes, i + 1) << "Should increment seen times";
        fakeTimers.advance(durationIncrease);
    }

    logger_log("TEST: Completed minIterations stage");

    fakeTimers.advance(durationIncrease);
    svc->processSignal(HIGH, &status);
    EXPECT_TRUE(status.stateChanged) << "Should have changed state";
    EXPECT_EQ(status.currentState, LOW) << "Should have HIGH value";
    EXPECT_EQ(status.seenSignalTimes, minIterations + 1) << "Should increment seen times";
    EXPECT_EQ(status.seenSignalSince, nowMillis) << "Should remember first time seen signal";
}

TEST_F(SwitchServiceTest, DoesntChangeStateOnLow)
{
    const int seenSignalTimes = test::randomNumber(100, 600);
    const unsigned int seenSignalSince = test::randomNumber(100, 600);
    switch_service::SwitchStatus status(HIGH, false, seenSignalTimes, seenSignalSince);

    int durationIncrease = minSignalDurationMs / minIterations;

    for (int i = 0; i < minIterations * 3; i++)
    {
        svc->processSignal(LOW, &status);
        EXPECT_FALSE(status.stateChanged) << "Should not have changed state";
        EXPECT_EQ(status.currentState, HIGH) << "Should not have toggled state";
        EXPECT_EQ(status.seenSignalTimes, seenSignalTimes) << "Should increment seen times";
        EXPECT_EQ(status.seenSignalSince, seenSignalSince) << "Should remember first time seen signal";
        fakeTimers.advance(durationIncrease);
    }
}

TEST_F(SwitchServiceTest, ApplyChanges)
{
    const int seenSignalTimes = test::randomNumber(100, 600);
    const unsigned int seenSignalSince = test::randomNumber(100, 600);
    switch_service::SwitchStatus status(HIGH, true, seenSignalTimes, seenSignalSince);
    svc->applyStateChange(&status);
    EXPECT_FALSE(status.stateChanged) << "Should have reset changed flag";
    EXPECT_EQ(status.currentState, HIGH) << "Should not have change current state";
    EXPECT_EQ(status.seenSignalTimes, 0) << "Should reset seen times";
    EXPECT_EQ(status.seenSignalSince, 0) << "Should reset first time seen signal";
}

} // namespace
