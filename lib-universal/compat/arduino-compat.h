#ifndef arduino_compat_h
#define arduino_compat_h

#ifndef ARDUINO
#define HIGH 0x1
#define LOW  0x0

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

#else
#include <Arduino.h>
#endif

#endif