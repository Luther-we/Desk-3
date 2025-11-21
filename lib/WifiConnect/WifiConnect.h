#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include "ProjectConfig.h"

struct WifiConfig {
  const char* ssid;
  const char* password;
  IPAddress   localIP;
  IPAddress   gateway;
  IPAddress   subnet;
  IPAddress   dns1;
  IPAddress   dns2;
  const char* hostname;
};

void wifiSetup(const WifiConfig& cfg);


void wifiLoop();


bool wifiIsConnected();
