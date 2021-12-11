#include <Arduino.h>
#include <SensorUS.h>

void SensorUS::begin(uint8_t trig, uint8_t echo)
{
    const float VEL_SONIDO = 34300.0; // Velocidad del sonido en cm/s
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

    unsigned long tiempo = pulseIn(pinEcho, HIGH);

    float distancia = tiempo * 0.000001 * VEL_SONIDO / 2.0;

    return distancia;
}

boolean SensorUS::checkDist(float umbral)
{
    if (dist() < umbral)
        return true;
    else
        return false;
}