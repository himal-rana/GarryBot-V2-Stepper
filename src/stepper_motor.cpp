#include "stepper_motor.h"
#include "config.h"

void StepperMotorController::begin()
{
    pinMode(LEFT_STEP_PIN, OUTPUT);
    pinMode(LEFT_DIR_PIN, OUTPUT);
    pinMode(LEFT_EN_PIN, OUTPUT);

    pinMode(RIGHT_STEP_PIN, OUTPUT);
    pinMode(RIGHT_DIR_PIN, OUTPUT);
    pinMode(RIGHT_EN_PIN, OUTPUT);

    digitalWrite(LEFT_STEP_PIN, LOW);
    digitalWrite(RIGHT_STEP_PIN, LOW);

    disable();

    setDirection(true);
}

void StepperMotorController::enable()
{
    // TMC2209 enable is active LOW
    digitalWrite(LEFT_EN_PIN, LOW);
    digitalWrite(RIGHT_EN_PIN, LOW);

    enabled = true;
}

void StepperMotorController::disable()
{
    digitalWrite(LEFT_EN_PIN, HIGH);
    digitalWrite(RIGHT_EN_PIN, HIGH);

    enabled = false;
}

bool StepperMotorController::isEnabled() const
{
    return enabled;
}

void StepperMotorController::setDirection(bool forward)
{
    directionForward = forward;

    digitalWrite(
        LEFT_DIR_PIN,
        forward ? HIGH : LOW
    );

    // Right motor is mechanically mirrored
    digitalWrite(
        RIGHT_DIR_PIN,
        forward ? LOW : HIGH
    );
}

void StepperMotorController::setSpeed(float stepsPerSecond)
{
    targetSpeed = stepsPerSecond;

    if (targetSpeed == 0.0f)
    {
        stepInterval = 0;
        return;
    }

    if (targetSpeed > 0.0f)
    {
        setDirection(true);
    }
    else
    {
        setDirection(false);
    }

    float speedMagnitude = fabs(targetSpeed);

    stepInterval =
        (unsigned long)(
            1000000.0f / speedMagnitude
        );
}

void StepperMotorController::stop()
{
    targetSpeed = 0.0f;
    stepInterval = 0;
}

void StepperMotorController::update()
{
    if (!enabled)
        return;

    if (stepInterval == 0)
        return;

    unsigned long now = micros();

    if (now - lastStepTime >= stepInterval)
    {
        lastStepTime = now;

        digitalWrite(LEFT_STEP_PIN, HIGH);
        digitalWrite(RIGHT_STEP_PIN, HIGH);

        delayMicroseconds(2);

        digitalWrite(LEFT_STEP_PIN, LOW);
        digitalWrite(RIGHT_STEP_PIN, LOW);
    }
}