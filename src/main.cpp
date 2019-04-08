#include "Arduino.h"
#include "CD74HC4067.h"

const int selectPins[4] = { 5, 4, 3, 2 };
const int sig = 6;
const int en = 7;

CD74HC4067 switchInput(5, 4, 3, 2);

void setup() {
    for (int i=0; i<3; i++)
    {
        pinMode(selectPins[i], OUTPUT);
        digitalWrite(selectPins[i], LOW);
    }
    pinMode(en, OUTPUT);
    pinMode(sig, INPUT_PULLUP);
    digitalWrite(en, LOW);
    Serial.begin(9600);
}

void loop() {
    delay(1000);
    Serial.println("Reading channels");

    const unsigned long readStart = micros();
    for(int i = 0; i < 16; i++) {
        switchInput.channel(i);
        const int value = digitalRead(sig);
        Serial.print("Bit ");
        Serial.print(i);
        Serial.print(": ");
        Serial.println(value);
    }
    const unsigned long readEnd = micros();
    const unsigned long readTaken = readEnd - readStart;
    Serial.print("Reading taken: ");
    Serial.print(readTaken);
    Serial.println("mks");
}
