#include "pid_tuner.h"
#include <Arduino.h>

PIDTuner::PIDTuner(int kpPin, int kiPin, int kdPin)
{
    this->kpPin = kpPin;
    this->kiPin = kiPin;
    this->kdPin = kdPin;
}

void PIDTuner::begin()
{
    pinMode(kpPin, INPUT);
    pinMode(kiPin, INPUT);
    pinMode(kdPin, INPUT);
}

float PIDTuner::mapFloat(float x,
                         float in_min,
                         float in_max,
                         float out_min,
                         float out_max)
{
    return (x - in_min) * (out_max - out_min)
           / (in_max - in_min) + out_min;
}

// Read the sample potentiometer values and average them to reduce noise. Then map the averaged value to the desired range for each PID gain.
float PIDTuner::getKp()
{
    long sum = 0;

    for (int i = 0; i < 10; i++)
    {
        sum += analogRead(kpPin);
    }

    float average = sum / 10.0f;

    return mapFloat(average, 0, 1023, 9.6f, 10.3f);
}

float PIDTuner::getKi()
{
    long sum = 0;

    for (int i = 0; i < 10; i++)
    {
        sum += analogRead(kiPin);
    }

    float average = sum / 10.0f;

    return mapFloat(average, 0, 1023, 0.0f, 0.5f);
}

float PIDTuner::getKd()
{
    long sum = 0;

    for (int i = 0; i < 10; i++)
    {
        sum += analogRead(kdPin);
    }

    float average = sum / 10.0f;

    return mapFloat(average, 0, 1023, 0.4f, 0.6f);
}