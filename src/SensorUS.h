#pragma once

#include <stdint.h>

class SensorUS
{
private:
    const float VEL_SONIDO = 34300.0; // Velocidad del sonido en cm/s
    uint8_t pinTrig;
    uint8_t pinEcho;

public:
    void begin(uint8_t trig, uint8_t echo);
    float dist();
    boolean checkDist(float umbral);
};