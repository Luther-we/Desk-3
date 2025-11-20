#pragma once
#include <stdint.h>



// Publie température + humidité sur les topics capteurs
void mqttPublishDht(float temperature);

// Publie la discovery Home Assistant (light + temp + hum)
void mqttPublishDiscovery();
