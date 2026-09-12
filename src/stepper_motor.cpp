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

    currentSpeed = 0.0f;
    targetSpeed = 0.0f;

    lastStepTime = micros();
    lastSpeedUpdate = micros();

    disable();
    directionForward = false;
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

    currentSpeed = 0.0f;
    targetSpeed = 0.0f;
}

bool StepperMotorController::isEnabled() const
{
    return enabled;
}

void StepperMotorController::setDirection(bool forward)
{
    // Only update DIR pins if direction actually changes
    if (directionForward == forward)
        return;

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
    // PID only sets the target.
    // update() will ramp toward this speed.
    targetSpeed = stepsPerSecond;
}

void StepperMotorController::stop()
{
    targetSpeed = 0.0f;
    currentSpeed = 0.0f;
}

void StepperMotorController::update()
{
    if (!enabled)
        return;

    unsigned long now = micros();


    // ==============================================
    // Acceleration ramp
    // ==============================================

    float dt =
        (now - lastSpeedUpdate)
        / 1000000.0f;

    lastSpeedUpdate = now;

    // Protect against strange timing
    if (dt <= 0.0f)
        return;

    float maxSpeedChange =
        maxAcceleration * dt;


    if (targetSpeed > currentSpeed)
    {
        currentSpeed += maxSpeedChange;

        if (currentSpeed > targetSpeed)
        {
            currentSpeed = targetSpeed;
        }
    }
    else if (targetSpeed < currentSpeed)
    {
        currentSpeed -= maxSpeedChange;

        if (currentSpeed < targetSpeed)
        {
            currentSpeed = targetSpeed;
        }
    }


    // ==============================================
    // Stop region
    // ==============================================

    if (fabs(currentSpeed) < 1.0f)
    {
        currentSpeed = 0.0f;
        return;
    }


    // ==============================================
    // Direction
    // ==============================================

    bool forward =
        currentSpeed > 0.0f;

    setDirection(forward);


    // ==============================================
    // Step interval
    // ==============================================

    float speedMagnitude =
        fabs(currentSpeed);

    unsigned long stepInterval =
        (unsigned long)(
            1000000.0f /
            speedMagnitude
        );


    // ==============================================
    // Generate step pulse
    // ==============================================

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