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
    // Requested speed from PID
    float targetSpeed = 0.0f;

    // Actual speed used for step generation
    float currentSpeed = 0.0f;

    // Maximum rate of speed change
    float maxAcceleration = 30000.0f;   // steps/s^2

    bool enabled = false;

    unsigned long lastStepTime = 0;
    unsigned long lastSpeedUpdate = 0;

    bool directionForward = true;

    void setDirection(bool forward);
};

#endif