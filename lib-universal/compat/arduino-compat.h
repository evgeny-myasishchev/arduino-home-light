#ifndef arduino_compat_h
#define arduino_compat_h

#ifndef ARDUINO
#define HIGH 0x1
#define LOW  0x0
#else
#include <Arduino.h>
#endif

#endif