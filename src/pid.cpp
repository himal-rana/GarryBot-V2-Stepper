#include "pid.h"

PID::PID(float kp, float ki, float kd)
{
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;

    integral = 0.0f;
    previousError = 0.0f;

    // Generic PID output limit
    outputLimit = 800.0f;
}

float PID::compute(float error, float dt)
{
    // Protect against invalid dt
    if (dt <= 0.0f)
    {
        return 0.0f;
    }

    // Integral
    integral += error * dt;

    // Integral anti-windup
    if (integral > 100.0f)
        integral = 100.0f;

    if (integral < -100.0f)
        integral = -100.0f;

    // Derivative
    float derivative =
        (error - previousError) / dt;

    previousError = error;

    // PID
    float output =
        kp * error +
        ki * integral +
        kd * derivative;

    // Output limit
    if (output > outputLimit)
        output = outputLimit;

    if (output < -outputLimit)
        output = -outputLimit;

    return output;
}

void PID::reset()
{
    integral = 0.0f;
    previousError = 0.0f;
}

void PID::setGains(
    float kp,
    float ki,
    float kd
)
{
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;
}

void PID::setOutputLimit(float limit)
{
    outputLimit = limit;
}

float PID::getKp() const
{
    return kp;
}

float PID::getKi() const
{
    return ki;
}

float PID::getKd() const
{
    return kd;
}