#include <ArduinoUnit.h>
#include <timers.h>

test(defaultNowMillisProc)
{
  nowMillisProc nowMillis = defaultNowMillisProc();
  const unsigned long now = nowMillis();
  assertEqual(now, millis());
}