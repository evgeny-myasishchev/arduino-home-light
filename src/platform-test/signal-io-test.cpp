#include <ArduinoUnit.h>
#include <pstd.h>
#include "CD74HC4067.h"
#include <switches.h>

test(signal_io_reader)
{
    // In order to run this test make sure to:
    /*
        Connect multiplexer select pins to 5....2, signal: 6 and en 7
    */

    CD74HC4067 mux(5, 4, 3, 2);
    switches::CD74HC4067Config cfg(5, 4, 3, 2, 6, 7);
    switches::CD74HC4067SignalReader reader(cfg);
    
    reader.init();

    pinMode(cfg.sig, OUTPUT);

    mux.channel(5);
    digitalWrite(cfg.sig, HIGH);

    mux.channel(7);
    digitalWrite(cfg.sig, HIGH);

    pinMode(cfg.sig, INPUT_PULLUP);

    assertEqual(HIGH, reader.read(5));
    assertEqual(HIGH, reader.read(7));
}