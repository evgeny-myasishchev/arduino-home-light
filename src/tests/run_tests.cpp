#include <ArduinoUnit.h>

void setup()
{
  Serial.begin(9600);
  while(!Serial) {} // Portability for Leonardo/Micro
}

void loop()
{
  Test::run();
}