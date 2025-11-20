#include "MqttTemplates.h"
#include <ArduinoJson.h>
#include "MqttClient.h"
#include "MqttConfig.h"


void mqttPublishDht(float temperature) {
  if (isnan(temperature) ) {
    Serial.println("[DHT] Valeurs invalides, publish annule");
    return;
  }

  Serial.print("[DHT] T = ");
  Serial.print(temperature);

  char buf[16];

  dtostrf(temperature, 2, 2, buf);
  mqttClient().publish(t_temp_state.c_str(), buf, true);

}

void mqttPublishDiscovery() {
  
  // Temp sensor
  {
    JsonDocument doc;

    doc["name"]    = "Température";
    doc["uniq_id"] = String(DEVICE_NAME) + "_temperature";
    doc["obj_id"]  = String(DEVICE_NAME) + "_temperature";

    doc["stat_t"]  = t_temp_state;
    doc["unit_of_measurement"] = "°C";
    doc["device_class"]        = "temperature";
    doc["state_class"]         = "measurement";

    doc["avty_t"]       = t_avail;
    doc["pl_avail"]     = "online";
    doc["pl_not_avail"] = "offline";

    JsonObject dev = doc["device"].to<JsonObject>();
    dev["name"] = FRIENDLY_NAME;
    dev["mf"]   = "DIY";
    dev["mdl"]  = "ESP32 C3 - Desk #3";
    JsonArray ids = dev["identifiers"].to<JsonArray>();
    ids.add(DEVICE_NAME);

    char buf[512];
    size_t n = serializeJson(doc, buf, sizeof(buf));
    mqttClient().publish(t_temp_disc.c_str(), (const uint8_t*)buf, (unsigned int)n, true);
    Serial.printf("[DISCOVERY] TEMP %s\n", buf);
  }

}
