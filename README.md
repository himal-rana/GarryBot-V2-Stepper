# GarryBot-V2-Stepper

Successor to the original **GarryBot-V1-DC**.

## Overview

GarryBot-V2-Stepper is a two-wheeled self-balancing robot built around an ESP32, IMU MPU6050, NEMA17 stepper motors, and TMC2209 stepper drivers.

The main reason for moving from DC motors to stepper motors was to reduce the motor dead-zone and inconsistent low-speed response observed in the first GarryBot version. The stepper motors give more predictable wheel motion and provide a better platform for future work on position and motion control.

The robot estimates its pitch angle using simple complementary filter to fuse accelerometer and gyroscope data from the MPU6050. A PID control loop is used to generate the required wheel speed command. The ESP32 then converts the control output directly into step pulses for the TMC2209 drivers.

## Hardware

- ESP32 as microcontroller
- MPU6050 as IMU
- 2 × NEMA17 stepper motors
- 2 × TMC2209 stepper drivers
- 2 × wheels
- 3S 11.1V LiPo battery
- LM2596 as Buck converter for ESP32 power supply
- 3D printed robot frame
- Zip ties to affix battery
- Double sided tape to fix components on frame
- A Rocker switch

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
## System Architecture

The control flow of GarryBot-V2-Stepper is:

```text
MPU6050
   ↓
Accelerometer + Gyroscope
   ↓
Complementary Filter
   ↓
Filtered Pitch Angle
   ↓
PID Controller
   ↓
Target Stepper Speed
   ↓
Motor steps
   ↓
TMC2209 Drivers
   ↓
NEMA17 Motors
## Working Configuration

The following parameters produced a stable balancing response in the current prototype.

| Parameter | Value |
|---|---:|
| Control loop frequency | 250 Hz |
| Control interval | 4000 µs |
| Target balance angle | 13.8° |
| PID output limit | 3000 steps/s |
| Microstepping | 1/8 |
| Effective steps/revolution | 1600 |
| Stepper acceleration limit | 50,000 steps/s² |
| Complementary filter coefficient | 0.985 |

### PID Gains

```text
Kp = ...
Ki = ...
Kd = ...