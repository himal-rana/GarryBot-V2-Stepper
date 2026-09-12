#include <Arduino.h>
#include <Wire.h>
#include <math.h>

#include "config.h"
#include "imu.h"
#include "filter.h"
#include "pid.h"
#include "stepper_motor.h"

// ==================================================
// OBJECTS
// ==================================================

ComplementaryFilter pitchFilter;

PID pid(
    PID_KP,
    PID_KI,
    PID_KD
);

StepperMotorController motors;


// ==================================================
// TIMING
// ==================================================

unsigned long lastControlTime = 0;
unsigned long lastPrintTime = 0;
const unsigned long CONTROL_INTERVAL_US = 4000; // 250 Hz


// ==================================================
// SETUP
// ==================================================

void setup()
{
    Serial.begin(115200);
    delay(500);


    // ==============================================
    // I2C
    // ==============================================

    Wire.begin(
        I2C_SDA,
        I2C_SCL
    );


    // ==============================================
    // MPU6050
    // ==============================================

    initializeIMU();
    calibrateGyroscope();
    if (!readMPU6050())
    {
        Serial.println("MPU6050 initial read failed");

        while (1)
        {
            delay(100);
        }
    }


    // ==============================================
    // Initial accelerometer angle
    // ==============================================

    float ax =
        accelX_raw / 16384.0f;
    float ay =
        accelY_raw / 16384.0f;
    float az =
        accelZ_raw / 16384.0f;
    float accelPitch =
        atan2(
            -ax,
            sqrt(ay*ay+az*az)
        )
        * 180.0f / PI;
    // ==============================================
    // Initialize filter
    // ==============================================

    pitchFilter.reset(accelPitch);


    // ==============================================
    // PID
    // ==============================================

    pid.setOutputLimit(3000.0f);


    // ==============================================
    // Stepper motors
    // ==============================================

    motors.begin();
    motors.enable();
    motors.stop();


    // ==============================================
    // Timing
    // ==============================================

    lastControlTime = micros();
    Serial.println("Balance test started");
}


// ==================================================
// LOOP
// ==================================================

void loop()
{
    // ==============================================
    // Generate step pulses continuously
    // ==============================================

    motors.update();

    // ==============================================
    // Fixed control loop timing
    // ==============================================

    unsigned long now = micros();

    if (
        now - lastControlTime
        < CONTROL_INTERVAL_US
    )
    {
        return;
    }


    float dt =
        (now - lastControlTime)
        / 1000000.0f;
    lastControlTime = now;


    // ==============================================
    // Read MPU6050
    // ==============================================

    if (!readMPU6050())
    {
        motors.stop();
        return;
    }


    // ==============================================
    // Accelerometer
    // ==============================================

    float ax =
        accelX_raw / 16384.0f;
    float ay =
        accelY_raw / 16384.0f;
    float az =
        accelZ_raw / 16384.0f;
    float accelPitch =
        atan2(
            -ax,
            sqrt(
                ay * ay +
                az * az
            )
        )
        * 180.0f / PI;


    // ==============================================
    // Gyroscope
    // ==============================================

    float gyroRate =
        (gyroY_raw - gyroY_bias)
        / 131.0f;

    // ==============================================
    // Complementary filter
    // ==============================================

    float pitch =
        pitchFilter.update(
            accelPitch,
            gyroRate,
            dt
        );


    // ==============================================
    // Balance error
    // ==============================================

    float error =
        TARGET_ANGLE - pitch;


    // ==============================================
    // PID / Fall protection
    // ==============================================

    float controlOutput = 0.0f;
    float motorSpeed = 0.0f;


    if (fabs(error) > MAX_TILT)
    {
        motors.stop();

        pid.reset();
    }

    else
    {
        controlOutput =
            pid.compute(
                error,
                dt
            );


        // PID output directly represents
        // stepper speed in steps/s

        motorSpeed =
            -controlOutput;


        motors.setSpeed(
            motorSpeed
        );
    }


    // ==============================================
    // Debug
    // ==============================================

    if (
        millis() - lastPrintTime
        >= 200
    )
    {
        lastPrintTime =
            millis();


        Serial.print("Pitch: ");
        Serial.print(pitch, 2);

        Serial.print(" | Target: ");
        Serial.print(TARGET_ANGLE, 2);

        Serial.print(" | Error: ");
        Serial.print(error, 2);

        Serial.print(" | PID: ");
        Serial.print(controlOutput, 2);

        Serial.print(" | Speed: ");
        Serial.println(motorSpeed, 2);
    }
}