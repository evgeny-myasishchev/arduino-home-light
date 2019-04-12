#include <ArduinoUnit.h>
#include <Timers.h>
#include "FakeTimers.h"
#include <SwitchService.h>
#include <ArduinoLog.h>

test(PushButtonSwitchSwitchServiceChangeStateWhenSeenSignalEnough)
{
    unsigned int nowMillis = random(100, 600);
    int minSignalDurationMs = random(100, 500);
    int minIterations = random(10, 20);
    Log.trace("Use fake now: %d, minDuration: %d, minIterations: %d" CR, 
        nowMillis, 
        minSignalDurationMs, 
        minIterations);

    FakeTimers fakeTimers;
    fakeTimers.setMillis(nowMillis);

    SwitchServiceConfig cfg;
    cfg.minSignalDurationMs = minSignalDurationMs;
    cfg.minSignalIterations = minIterations;
    cfg.timers = &fakeTimers;
    SwitchService * svc = new PushButtonSwitchService(cfg);

    SwitchStatus status;

    int durationIncrease = minSignalDurationMs / minIterations;

    for(int i = 0; i < minIterations; i++) {
        svc->processSignal(HIGH, &status);
        assertFalse(status.stateChanged, "Should not have changed state");
        assertEqual(status.currentState, LOW, "Should not have toggled state");
        assertEqual(status.seenSignalSince, nowMillis, "Should remember first time seen signal");
        assertEqual(status.seenSignalTimes, i + 1, "Should increment seen times");
        fakeTimers.advance(durationIncrease);
    }

    fakeTimers.advance(durationIncrease);
    svc->processSignal(HIGH, &status);
    assertTrue(status.stateChanged, "Should not have changed state");
    assertEqual(status.currentState, HIGH, "Should have toggled state");
    assertEqual(status.seenSignalTimes, minIterations + 1, "Should increment seen times");
    assertEqual(status.seenSignalSince, nowMillis, "Should remember first time seen signal");
}