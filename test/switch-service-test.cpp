#include <Timers.h>
#include "mocks/FakeTimers.h"
#include <switch-service.h>
#include <gtest/gtest.h>
#include <arduino-compat.h>
#include <stdio.h>
#include <random>
#include "logger.h"
#include "test-lib/random.h"

TEST(switchService, ChangeStateHighWhenSeenSignalEnough)
{
    unsigned int nowMillis = test::randomNumber(100, 600);
    int minSignalDurationMs = test::randomNumber(100, 600);
    int minIterations = test::randomNumber(5, 10);
    logger_log("minIterations: %d", minIterations);

    FakeTimers * fakeTimers = new FakeTimers(nowMillis);

    switch_service::SwitchServiceConfig cfg = switch_service::SwitchServiceConfig(
        minSignalDurationMs,
        minIterations,
        fakeTimers);
    switch_service::SwitchService *svc = new switch_service::PushButtonSwitchService(cfg);

    switch_service::SwitchStatus status;

    int durationIncrease = minSignalDurationMs / minIterations;

    for (int i = 0; i < minIterations; i++)
    {
        svc->processSignal(HIGH, &status);
        EXPECT_FALSE(status.stateChanged) << "Should not have changed state";
        EXPECT_EQ(status.currentState, LOW) << "Should not have toggled state";
        EXPECT_EQ(status.seenSignalSince, nowMillis) << "Should remember first time seen signal";
        EXPECT_EQ(status.seenSignalTimes, i + 1) << "Should increment seen times";
        fakeTimers->advance(durationIncrease);
    }

    logger_log("TEST: Completed minIterations stage");

    fakeTimers->advance(durationIncrease);
    svc->processSignal(HIGH, &status);
    EXPECT_TRUE(status.stateChanged) << "Should have changed state";
    EXPECT_EQ(status.currentState, HIGH) << "Should have HIGH value";
    EXPECT_EQ(status.seenSignalTimes, minIterations + 1) << "Should increment seen times";
    EXPECT_EQ(status.seenSignalSince, nowMillis) << "Should remember first time seen signal";
}

TEST(switchService, DoesntChangeStateOnLow)
{
    unsigned int nowMillis = test::randomNumber(100, 600);
    int minSignalDurationMs = test::randomNumber(100, 600);
    int minIterations = test::randomNumber(5, 10);
    logger_log("minIterations: %d", minIterations);

    FakeTimers * fakeTimers = new FakeTimers(nowMillis);

    switch_service::SwitchServiceConfig cfg = switch_service::SwitchServiceConfig(
        minSignalDurationMs,
        minIterations,
        fakeTimers);
    switch_service::SwitchService *svc = new switch_service::PushButtonSwitchService(cfg);

    const int currentState = HIGH;
    const int seenSignalTimes = test::randomNumber(10, 100);
    const unsigned int seenSignalSince = test::randomNumber(nowMillis, nowMillis * 10);

    switch_service::SwitchStatus status = switch_service::SwitchStatus(
        currentState,
        false,
        seenSignalTimes,
        seenSignalSince
    );

    int durationIncrease = minSignalDurationMs / minIterations;

    for (int i = 0; i < minIterations * 2; i++)
    {
        svc->processSignal(LOW, &status);
        EXPECT_FALSE(status.stateChanged) << "Should not have changed state";
        EXPECT_EQ(status.currentState, currentState) << "Should not have toggled state";
        EXPECT_EQ(status.seenSignalSince, seenSignalSince) << "Should not change seen since";
        EXPECT_EQ(status.seenSignalTimes, seenSignalTimes) << "Should not increment seen times";
        fakeTimers->advance(durationIncrease);
    }
}