#ifndef PID_TUNER_H
#define PID_TUNER_H

class PIDTuner
{
public:
    PIDTuner(int kpPin, int kiPin, int kdPin);

    void begin();

    float getKp();
    float getKi();
    float getKd();

private:
    int kpPin;
    int kiPin;
    int kdPin;

    float mapFloat(float x,
                   float inMin, float inMax,
                   float outMin, float outMax);
};

#endif