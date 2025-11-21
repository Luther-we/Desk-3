// lib/ServoMotor/ServoMotor.h
#pragma once
#include <Arduino.h>

struct ServoConfig {
  int pin;
  int minAngle;  // ex: 0
  int maxAngle;  // ex: 180
  int minUs;     // ex: 500  (impulsion min en µs)
  int maxUs;     // ex: 2400 (impulsion max en µs)
};

void servoSetup(const ServoConfig& cfg);
void servoLoop();

// API pour le reste du code
void servoSetTargetAngle(int angle); // degrés 0–180
int  servoCurrentAngle();
