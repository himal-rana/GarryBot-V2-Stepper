// #include <Arduino.h>
// #include <Wire.h>
// #include <math.h>

// #include "config.h"
// #include "imu.h"
// #include "filter.h"
// #include "pid.h"
// #include "display.h"
// #include "stepper_motor.h"

// // ==================================================
// // OBJECTS
// // ==================================================

// ComplementaryFilter pitchFilter;

// PID pid(
//     PID_KP,
//     PID_KI,
//     PID_KD
// );

// StepperMotorController motors;


// // ==================================================
// // TIMING
// // ==================================================

// unsigned long lastControlTime = 0;

// unsigned long lastDisplayTime = 0;

// const unsigned long DISPLAY_INTERVAL = 100;


// // ==================================================
// // SETUP
// // ==================================================

// void setup()
// {
//     Serial.begin(115200);

//     delay(500);

//     Serial.println();
//     Serial.println("==============================");
//     Serial.println("      GarryBot Stepper");
//     Serial.println("==============================");


//     // ----------------------------------------------
//     // I2C
//     // ----------------------------------------------

//     Wire.begin(I2C_SDA, I2C_SCL);


//     // ----------------------------------------------
//     // IMU
//     // ----------------------------------------------

//     initializeIMU();

//     calibrateGyroscope();

//     readMPU6050();


//     // ----------------------------------------------
//     // Initial accelerometer pitch
//     // ----------------------------------------------

//     float ax = accelX_raw / 16384.0f;
//     float ay = accelY_raw / 16384.0f;
//     float az = accelZ_raw / 16384.0f;

//     float accelPitch =
//         atan2(
//             -ax,
//             sqrt(
//                 ay * ay +
//                 az * az
//             )
//         )
//         * 180.0f / PI;


//     // ----------------------------------------------
//     // Initialize complementary filter
//     // ----------------------------------------------

//     pitchFilter.reset(accelPitch);


//     // ----------------------------------------------
//     // Motors
//     // ----------------------------------------------

//     motors.begin();

//     motors.enable();

//     motors.stop();


//     // ----------------------------------------------
//     // OLED
//     // ----------------------------------------------

//     displayInit();


//     // ----------------------------------------------
//     // Timing
//     // ----------------------------------------------

//     lastControlTime = micros();


//     Serial.println("Initialization complete.");
// }


// // ==================================================
// // LOOP
// // ==================================================

// void loop()
// {
//     // ==================================================
//     // STEP GENERATION
//     // ==================================================

//     // Must run continuously.
//     // Do NOT put delays in loop().
//     motors.update();


//     // ==================================================
//     // CONTROL LOOP TIMING
//     // ==================================================

//     unsigned long now = micros();

//     float dt =
//         (now - lastControlTime)
//         / 1000000.0f;

//     lastControlTime = now;


//     // ==================================================
//     // READ MPU6050
//     // ==================================================

//     readMPU6050();


//     // ==================================================
//     // ACCELEROMETER
//     // ==================================================

//     float ax = accelX_raw / 16384.0f;
//     float ay = accelY_raw / 16384.0f;
//     float az = accelZ_raw / 16384.0f;


//     // ==================================================
//     // ACCELEROMETER PITCH
//     // ==================================================

//     float accelPitch =
//         atan2(
//             -ax,
//             sqrt(
//                 ay * ay +
//                 az * az
//             )
//         )
//         * 180.0f / PI;


//     // ==================================================
//     // GYROSCOPE
//     // ==================================================

//     float gyroRate =
//         (gyroY_raw - gyroY_bias)
//         / 131.0f;


//     // ==================================================
//     // COMPLEMENTARY FILTER
//     // ==================================================

//     float pitch =
//         pitchFilter.update(
//             accelPitch,
//             gyroRate,
//             dt
//         );


//     // ==================================================
//     // BALANCE ERROR
//     // ==================================================

//     float error =
//         TARGET_ANGLE - pitch;


//     // ==================================================
//     // FALL PROTECTION
//     // ==================================================

//     if (fabs(error) > MAX_TILT)
//     {
//         motors.stop();

//         pid.reset();

//         return;
//     }


//     // ==================================================
//     // PID
//     // ==================================================

//     int controlOutput =
//         pid.compute(
//             error,
//             dt
//         );


//     // ==================================================
//     // STEPPER SPEED
//     // ==================================================

//     motors.setSpeed(
//         controlOutput
//     );


//     // ==================================================
//     // SERIAL DEBUG
//     // ==================================================

//     Serial.print("Pitch: ");
//     Serial.print(pitch, 2);

//     Serial.print(" | Error: ");
//     Serial.print(error, 2);

//     Serial.print(" | PID: ");
//     Serial.println(controlOutput);


//     // ==================================================
//     // OLED
//     // ==================================================

//     if (
//         millis() - lastDisplayTime
//         >= DISPLAY_INTERVAL
//     )
//     {
//         lastDisplayTime = millis();

//         // We will modify displayShow()
//         // for the stepper robot next.
//     }
// }
#include <Arduino.h>

#include "config.h"
#include "stepper_motor.h"

StepperMotorController motors;

void setup()
{
    Serial.begin(115200);

    motors.begin();
    motors.enable();

    motors.setSpeed(500);
}

void loop()
{
    motors.update();
}