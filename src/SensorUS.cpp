#include <Arduino.h>

void SensorUS::begin(uint8_t trig, uint8_t echo) 
{
    pinTrig = trig;
    pinEcho = echo;

    pinMode(pinTrig, OUTPUT);
    pinMode(pinEcho, INPUT);
}

float SensorUS::dist()
{
    digitalWrite(pinTrig, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinTrig, LOW);
    pulseIn(pinEcho, HIGH);
}