#include "MqttTemplates.h"
#include <ArduinoJson.h>
#include "MqttClient.h"
#include "Topics.h"
#include "ProjectConfig.h"
#include "SensorProfile.h"



void mqttPublishSht(float temperature, float humidity) {
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("[SHT] Valeurs invalides, publish annule");
    return;
  }

  Serial.print("[SHT] T = ");
  Serial.print(temperature);
  Serial.print("[SHT] H = ");
  Serial.print(humidity);

  char buf[16];

  dtostrf(temperature, 2, 2, buf);
  mqttClient().publish(Topics::tempState().c_str(), buf, true);
  dtostrf(humidity, 2, 2, buf);
  mqttClient().publish(Topics::humState().c_str(), buf, true);

}

void mqttPublishDiscovery() {
  
  // SHT31 Temperature
  {
    JsonDocument doc;

    doc["name"]    = "Température";
    doc["uniq_id"] = String(ProjectConfig::deviceName()) + "_temperature";
    doc["obj_id"]  = String(ProjectConfig::deviceName()) + "_temperature";

    doc["stat_t"]  = Topics::tempState();
    doc["unit_of_measurement"] = "°C";
    doc["device_class"]        = "temperature";
    doc["state_class"]         = "measurement";

    doc["avty_t"]       = Topics::availability();
    doc["pl_avail"]     = "online";
    doc["pl_not_avail"] = "offline";

    JsonObject dev = doc["device"].to<JsonObject>();
    dev["name"] = ProjectConfig::friendlyName();
    dev["mf"]   = "DIY";
    dev["mdl"]  = "ESP32 C3 - Desk #3";
    JsonArray ids = dev["identifiers"].to<JsonArray>();
    ids.add(ProjectConfig::deviceName());

    char buf[512];
    size_t n = serializeJson(doc, buf, sizeof(buf));
    mqttClient().publish(Topics::tempDiscovery().c_str(), (const uint8_t*)buf, (unsigned int)n, true);
    Serial.printf("[DISCOVERY] TEMP %s\n", buf);
  }

  {
    JsonDocument doc;

    doc["name"]    = "Humidité";
    doc["uniq_id"] = String(ProjectConfig::deviceName()) + "_humidity";
    doc["obj_id"]  = String(ProjectConfig::deviceName()) + "_humidity";

    doc["stat_t"]  = Topics::humState();
    doc["unit_of_measurement"] = "%";
    doc["device_class"]        = "humidity";
    doc["state_class"]         = "measurement";

    doc["avty_t"]       = Topics::availability();
    doc["pl_avail"]     = "online";
    doc["pl_not_avail"] = "offline";

    JsonObject dev = doc["device"].to<JsonObject>();
    dev["name"] = ProjectConfig::friendlyName();
    dev["mf"]   = "DIY";
    dev["mdl"]  = "ESP32 C3 - Desk #3";
    JsonArray ids = dev["identifiers"].to<JsonArray>();
    ids.add(ProjectConfig::deviceName());

    char buf[512];
    size_t n = serializeJson(doc, buf, sizeof(buf));
    mqttClient().publish(Topics::humDiscovery().c_str(), (const uint8_t*)buf, (unsigned int)n, true);
    Serial.printf("[DISCOVERY] HUM %s\n", buf);
  }

  {
  JsonDocument doc;

  doc["name"]    = "Servo angle";
  doc["uniq_id"] = String(ProjectConfig::deviceName()) + "_servo_angle";
  doc["obj_id"]  = String(ProjectConfig::deviceName()) + "_servo_angle";

  doc["cmd_t"]   = Topics::servoCommand();
  doc["stat_t"]  = Topics::servoState();
  doc["min"]     = SensorProfile::SERVO_MIN_ANGLE;
  doc["max"]     = SensorProfile::SERVO_MAX_ANGLE;
  doc["step"]    = 1;

  JsonObject dev = doc["device"].to<JsonObject>();
  dev["name"] = ProjectConfig::friendlyName();
  dev["mf"]   = "DIY";
  dev["mdl"]  = "ESP32 C3 - Desk #3";

  JsonArray ids = dev["identifiers"].to<JsonArray>();
  ids.add(ProjectConfig::deviceName());

  char buf[512];
  size_t n = serializeJson(doc, buf, sizeof(buf));
  mqttClient().publish(
    Topics::servoDiscovery().c_str(),
    (const uint8_t*)buf,
    (unsigned int)n,
    true
  );
}

}
