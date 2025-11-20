#include "MqttConfig.h"
#include "MqttSecrets.h"

// Tu pourras passer ça en secrets PlatformIO plus tard
#ifndef MQTT_HOST
  #define MQTT_HOST
#endif

#ifndef MQTT_PORT
  #define MQTT_PORT
#endif

#ifndef MQTT_USER
  #define MQTT_USER
#endif

#ifndef MQTT_PASSWD
  #define MQTT_PASSWD
#endif

// Identité
const char* const DEVICE_NAME   = "TemplateDevice"; // utile pour id, sans espaces ni caractères spéciaux
const char* const FRIENDLY_NAME = "Template device";

// Topics
// ---- A EDITER ----
String t_base   = String(DEVICE_NAME) + "/";

String t_avail  = t_base + "status";

String t_temp_state = t_base + "sensor/temperature";
String t_temp_disc  = "homeassistant/sensor/" + String(DEVICE_NAME) + "_temperature/config";

const MqttConfig MQTT_CONFIG = {
  .host     = MQTT_HOST,
  .port     = MQTT_PORT,
  .user     = MQTT_USER,
  .password = MQTT_PASSWD
};
