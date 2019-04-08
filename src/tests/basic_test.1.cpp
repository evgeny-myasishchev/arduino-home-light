#include <ArduinoUnit.h>

test(correct1)
{
  int x=1;
  assertEqual(x,1);
}

test(incorrect2)
{
  int x=1;
  assertNotEqual(x,1);
}