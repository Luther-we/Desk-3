#pragma once
#include <Arduino.h>


namespace ProjectProfile {
  inline constexpr char DEVICE_NAME[]   = "desk3";
  inline constexpr char FRIENDLY_NAME[] = "Desk 3";
  
  inline constexpr uint8_t STATIC_IP_LAST_OCTET = 21;

  inline constexpr char MQTT_BASE_PREFIX[] = "desk3/";
}
