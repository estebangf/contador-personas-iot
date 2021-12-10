#pragma once

#include <stdint.h>

class SensorUS
{
private:
    uint8_t pinTrig;
    uint8_t pinEcho;

public:
    void begin(uint8_t trig, uint8_t echo);
    float dist();
    bool checkDist();
};