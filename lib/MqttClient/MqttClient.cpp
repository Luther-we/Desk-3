#include <WiFi.h>
#include <PubSubClient.h>
#include "MqttClient.h"
#include "ProjectProfile.h"
#include "ProjectConfig.h"
#include "Topics.h"

static WiFiClient   g_wifiClient;
static PubSubClient g_mqtt(g_wifiClient);

PubSubClient& mqttClient() {
  return g_mqtt;
}

void mqttSetup() {
  g_mqtt.setServer(ProjectConfig::mqttHost(), ProjectConfig::mqttPort());
  g_mqtt.setBufferSize(512);
  g_mqtt.setKeepAlive(30);
  g_mqtt.setSocketTimeout(15);
}

bool mqttEnsureConnected() {
  if (g_mqtt.connected()) return false;

  while (!g_mqtt.connected()) {
    String clientId = String(ProjectConfig::deviceName()) + "_" + String((uint32_t)ESP.getEfuseMac(), HEX);
    Serial.printf("[MQTT] Connexion a %s:%u ...\n", ProjectConfig::mqttHost(), ProjectConfig::mqttPort());

    bool ok = g_mqtt.connect(
      clientId.c_str(),
      ProjectConfig::mqttUser(),
      ProjectConfig::mqttPassword(),
      Topics::availability().c_str(),   // Last Will topic
      0,
      true,
      "offline"
    );

    if (ok) {
      Serial.println("[MQTT] Connecte !");
      g_mqtt.publish(Topics::availability().c_str(), "online", true);
      return true;
    } else {
      Serial.printf("[MQTT] Echec (state=%d), retry...\n", g_mqtt.state());
      delay(1500);
    }
  }
  return true;
}

void mqttLoop() {
  g_mqtt.loop();
}
