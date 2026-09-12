# GarryBot-V2-Stepper

Successor to the original **GarryBot-V1-DC**.

## Overview

GarryBot-V2-Stepper is a two-wheeled self-balancing robot built around an ESP32, MPU6050 IMU, NEMA17 stepper motors, and TMC2209 stepper drivers.

The main reason for moving from DC motors to stepper motors was to reduce the motor dead-zone and inconsistent low-speed response observed in the first GarryBot version. The stepper-based drivetrain gives more predictable wheel motion and provides a better platform for future work on position and motion control.

The robot estimates its pitch angle using accelerometer and gyroscope data from the MPU6050. A complementary filter is used for angle estimation, and a PID controller generates the required wheel speed command. The ESP32 then converts the control output directly into step pulses for the TMC2209 drivers.

## Hardware

- ESP32 development board
- MPU6050 IMU
- 2 × NEMA17 stepper motors
- 2 × TMC2209 stepper drivers
- 2 × wheels
- 2S LiPo battery / suitable power supply
- Buck converter for regulated electronics supply
- Robot chassis and mounting hardware

### Stepper Motor

- Model: 17HS3401S / 42SHDC3030Z-23WB-1
- Step angle: 1.8°
- Rated current: 1.0 A/phase
- Full steps per revolution: 200
- Microstepping used: 1/8
- Effective steps per revolution: 1600

## Pin Configuration

### MPU6050

| Signal | ESP32 |
|---|---|
| SDA | GPIO21 |
| SCL | GPIO22 |
| VCC | Regulated supply |
| GND | GND |

### Left TMC2209

| Signal | ESP32 |
|---|---|
| STEP | GPIO25 |
| DIR | GPIO26 |
| EN | GPIO27 |

### Right TMC2209

| Signal | ESP32 |
|---|---|
| STEP | GPIO32 |
| DIR | GPIO33 |
| EN | GPIO14 |

The right motor direction is inverted in software because the two motors are mounted as mirrored wheel drives.