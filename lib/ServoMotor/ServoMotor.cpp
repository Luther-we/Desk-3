// lib/ServoMotor/ServoMotor.cpp
#include "ServoMotor.h"
#include <ESP32Servo.h>

static Servo      g_servo;
static ServoConfig g_cfg;
static int        g_currentAngle = 0;
static int        g_targetAngle  = 0;
static bool       g_attached     = false;

void servoSetup(const ServoConfig& cfg) {
  g_cfg = cfg;

  // Attache le servo
  g_servo.setPeriodHertz(50); // 50 Hz standard
  g_servo.attach(
    g_cfg.pin,
    g_cfg.minUs,
    g_cfg.maxUs
  );
  g_attached = true;

  g_currentAngle = 0;
  g_targetAngle  = 0;
  g_servo.write(g_currentAngle);

  Serial.printf("[SERVO] Attaché sur GPIO %d\n", g_cfg.pin);
}

void servoSetTargetAngle(int angle) {
  if (!g_attached) return;

  // Clamp dans la plage autorisée
  if (angle < g_cfg.minAngle) angle = g_cfg.minAngle;
  if (angle > g_cfg.maxAngle) angle = g_cfg.maxAngle;

  g_targetAngle = angle;
}

int servoCurrentAngle() {
  return g_currentAngle;
}

void servoLoop() {
  if (!g_attached) return;

  // Ici on pourrait lisser le mouvement si tu veux.
  // Pour l'instant: on va direct au target si différent.
  if (g_currentAngle != g_targetAngle) {
    g_currentAngle = g_targetAngle;
    g_servo.write(g_currentAngle);
    // Pas de Serial.println ici pour éviter de spammer
  }
}
