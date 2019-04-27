#include <Timers.h>
#include "mocks/FakeTimers.h"
#include <switch-service.h>
#include <gtest/gtest.h>
#include <arduino-compat.h>
#include <stdio.h>
#include <random>
#include "logger.h"
#include "test-lib/random.h"
#include "test-lib/test-logger.h"


TEST(switchService, ChangeStateWhenSeenSignalEnough)
{
    setup_test_logger();

    unsigned int nowMillis = test::randomNumber(100, 600);
    int minSignalDurationMs = test::randomNumber(100, 600);
    int minIterations = test::randomNumber(100, 600);

    FakeTimers fakeTimers = FakeTimers(nowMillis);

    SwitchServiceConfig cfg = SwitchServiceConfig(
        minSignalDurationMs,
        minIterations,
        &fakeTimers
    );
    SwitchService * svc = new PushButtonSwitchService(cfg);

    SwitchStatus status;

    int durationIncrease = minSignalDurationMs / minIterations;

    for(int i = 0; i < minIterations; i++) {
        svc->processSignal(HIGH, &status);
        // EXPECT_TRUE(status.stateChanged) << "Should not have changed state";
        // EXPECT_EQ(status.currentState, LOW) << "Should not have toggled state";
        // EXPECT_EQ(status.seenSignalSince, nowMillis) << "Should remember first time seen signal";
        // EXPECT_EQ(status.seenSignalTimes, i + 1) << "Should increment seen times";
        // fakeTimers.advance(durationIncrease);
    }

    // fakeTimers.advance(durationIncrease);
    // svc->processSignal(HIGH, &status);
    // EXPECT_TRUE(status.stateChanged) << "Should not have changed state";
    // EXPECT_EQ(status.currentState, HIGH) << "Should have toggled state";
    // EXPECT_EQ(status.seenSignalTimes, minIterations + 1) << "Should increment seen times";
    // EXPECT_EQ(status.seenSignalSince, nowMillis) << "Should remember first time seen signal";
}