#pragma once
#include <stdint.h>



// Publie température + humidité sur les topics capteurs
void mqttPublishSht(float temperature, float humidity);

// Publie la discovery Home Assistant (light + temp + hum)
void mqttPublishDiscovery();
