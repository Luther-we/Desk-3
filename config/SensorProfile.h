#pragma once
#include <Arduino.h>

namespace SensorProfile {
  // SHT31
  inline constexpr int I2C_SDA = 8;
  inline constexpr int I2C_SCL = 9;

  inline constexpr unsigned long SHT31_INTERVAL_MS = 5000;

// Servo
  inline constexpr int SERVO_PIN = 7;

// Plage d’angle logique
  inline constexpr int SERVO_MIN_ANGLE = 0;
  inline constexpr int SERVO_MAX_ANGLE = 180;



}