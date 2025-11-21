#pragma once
#include <Arduino.h>

struct Sht31Config {
  int sdaPin;
  int sclPin;
  unsigned long intervalMs;
};

// Callback appelée à chaque nouvelle mesure valide
using Sht31Callback = void(*)(float temperature, float humidity);

void sht31Setup(const Sht31Config& cfg, Sht31Callback cb);
void sht31Loop();
