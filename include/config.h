#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ===============================
// I2C
// ===============================

constexpr uint8_t I2C_SDA = 21;
constexpr uint8_t I2C_SCL = 22;

// ===============================
// MPU6050
// ===============================

constexpr uint8_t MPU6050_ADDRESS = 0x68;

// ===============================
// OLED
// ===============================

constexpr uint8_t OLED_ADDRESS = 0x3C;

// ===============================
// LEFT TMC2209
// ===============================

constexpr uint8_t LEFT_STEP_PIN = 25;
constexpr uint8_t LEFT_DIR_PIN  = 26;
constexpr uint8_t LEFT_EN_PIN   = 27;

// ===============================
// RIGHT TMC2209
// ===============================

constexpr uint8_t RIGHT_STEP_PIN = 32;
constexpr uint8_t RIGHT_DIR_PIN  = 33;
constexpr uint8_t RIGHT_EN_PIN   = 14;

// ===============================
// BALANCE
// ===============================

constexpr float TARGET_ANGLE = 0.0f;

constexpr float MAX_TILT = 30.0f;

// Temporary PID values
constexpr float PID_KP = 10.8f;
constexpr float PID_KI = 0.0f;
constexpr float PID_KD = 0.19f;

#endif