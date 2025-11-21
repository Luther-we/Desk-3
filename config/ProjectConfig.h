// config/ProjectConfig.h
#pragma once
#include <Arduino.h>
#include "ProjectProfile.h"

// WIFI_SSID, WIFI_PASS, MQTT_HOST, MQTT_PORT, MQTT_USER, MQTT_PASSWD
// doivent venir de tes build_flags (variables d'env)

namespace ProjectConfig {

  // --- WiFi : valeurs de config ---

  inline IPAddress wifiLocalIP() {
    return IPAddress(192, 168, 1, ProjectProfile::STATIC_IP_LAST_OCTET);
  }

  inline IPAddress wifiGateway() {
    return IPAddress(192, 168, 1, 1);
  }

  inline IPAddress wifiSubnet() {
    return IPAddress(255, 255, 255, 0);
  }

  inline IPAddress wifiDns1() {
    return IPAddress(1, 1, 1, 1);
  }

  inline IPAddress wifiDns2() {
    return IPAddress(8, 8, 8, 8);
  }

  inline const char* wifiSsid() {
    return WIFI_SSID;
  }

  inline const char* wifiPass() {
    return WIFI_PASS;
  }

  inline const char* wifiHostname() {
    return ProjectProfile::DEVICE_NAME;
  }

  // --- MQTT : valeurs de config ---

  #ifndef MQTT_PORT
#define MQTT_PORT 1883
#endif

#ifndef MQTT_HOST
#define MQTT_HOST "127.0.0.1"
#endif

#ifndef MQTT_USER
#define MQTT_USER ""
#endif

#ifndef MQTT_PASS
#define MQTT_PASS ""
#endif

  inline const char* mqttHost()    { return MQTT_HOST; }
  inline uint16_t    mqttPort()    { return MQTT_PORT; }
  inline const char* mqttUser()    { return MQTT_USER; }
  inline const char* mqttPassword(){ return MQTT_PASS; }

  // Identité globale

  inline const char* deviceName()    { return ProjectProfile::DEVICE_NAME; }
  inline const char* friendlyName()  { return ProjectProfile::FRIENDLY_NAME; }

  // Base des topics (ex: "desk3/")
  inline String baseTopic() {
    return String(ProjectProfile::MQTT_BASE_PREFIX);
  }

}