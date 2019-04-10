#include <ArduinoUnit.h>

void setup()
{
  Serial.begin(9600);
  while(!Serial) {} // Portability for Leonardo/Micro

  Test::exclude("*");
  Test::include("dev_*");
}

void loop()
{
  Test::run();
}