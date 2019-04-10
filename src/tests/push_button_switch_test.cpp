#include <ArduinoUnit.h>
#include <Timers.h>
#include "FakeTimers.h"
#include <PushButtonSwitch.h>

test(PushButtonSwitchInitialState)
{
    pushButtonSwitchConfig cfg;
    PushButtonSwitch * btnSwitch = new PushButtonSwitch(cfg);
    assertEqual(btnSwitch->getState(), LOW);
}

test(dev_PushButtonSwitchLowLevelChangeWhenSeenSignalEnough)
{
    unsigned int nowMillis = random(100, 600);
    int minSignalDurationMs = random(100, 500);
    int minIterations = random(10, 20);

    FakeTimers fakeTimers;
    fakeTimers.setMillis(nowMillis);

    pushButtonSwitchConfig cfg;
    cfg.minSignalDurationMs = minSignalDurationMs;
    cfg.minSignalIterations = minIterations;
    cfg.timers = &fakeTimers;
    PushButtonSwitch * btnSwitch = new PushButtonSwitch(cfg);

    int durationIncrease = minSignalDurationMs / minIterations;

    for(int i = 0; i < minIterations; i++) {
        fakeTimers.advance(durationIncrease);
        btnSwitch->processCurrentLevel(HIGH);
        assertFalse(btnSwitch->hasStateChanged(), "Should not have changed state");
        assertEqual(btnSwitch->getState(), LOW, "Should not have toggled state");
    }

    fakeTimers.advance(durationIncrease);
    btnSwitch->processCurrentLevel(HIGH);
    assertTrue(btnSwitch->hasStateChanged(), "Should have changed state");
    assertEqual(btnSwitch->getState(), HIGH, "Should have toggled signal");

    btnSwitch->applyCurrentState();

    assertTrue(btnSwitch->hasStateChanged(), "Should have changed state");
    assertEqual(btnSwitch->getState(), HIGH, "Should stay HIGH");
}