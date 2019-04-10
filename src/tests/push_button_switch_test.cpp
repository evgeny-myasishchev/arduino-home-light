#include <ArduinoUnit.h>
#include <timers.h>
#include "FakeTimers.h"
#include <PushButtonSwitch.h>

test(PushButtonSwitchInitialState)
{
    // pushButtonSwitchConfig cfg;
    // PushButtonSwitch * btnSwitch = new PushButtonSwitch(cfg);
    // assertEqual(btnSwitch->getState(), LOW);

    // FakeTimers * fakeTimers = new FakeTimers();

    // fakeTimers->setMillis(1000);

    // assertEqual((unsigned long)1000, fakeTimers->millis());

    // nowMillisProc nowMillis = (nowMillisProc)&fakeTimers->millis;

    // assertEqual((unsigned long)1000, nowMillis());
}

test(PushButtonSwitchLowLevelDoesntChange)
{
    // pushButtonSwitchConfig cfg;
    // PushButtonSwitch * btnSwitch = new PushButtonSwitch(cfg);
    // assertEqual(btnSwitch->getState(), LOW);
}