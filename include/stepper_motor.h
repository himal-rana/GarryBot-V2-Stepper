#ifndef STEPPER_MOTOR_H
#define STEPPER_MOTOR_H

#include <Arduino.h>

class StepperMotorController
{
public:
    void begin();

    void enable();
    void disable();

    void setSpeed(float stepsPerSecond);

    void stop();

    void update();

    bool isEnabled() const;

private:
    float targetSpeed = 0.0f;

    bool enabled = false;

    unsigned long lastStepTime = 0;
    unsigned long stepInterval = 0;

    bool directionForward = true;

    void setDirection(bool forward);
};

#endif