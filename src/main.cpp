#include <Arduino.h>
#include "WifiConnect.h"
#include "WifiConfig.h"
#include "OTA.h"
#include "MqttClient.h"
#include "MqttTemplates.h"


void mqttCallback(char* topic, byte* payload, unsigned int length) {
  // Traiter les messages MQTT reçus ici
  Serial.printf("[MQTT] Message recu sur le topic %s: ", topic);
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void onConnectPublish() {
  mqttPublishDiscovery();
}

void setup() {
  Serial.begin(115200);
  
  uint32_t t0 = millis();
  while (!Serial && millis() - t0 < 3000) { delay(10); }
  Serial.println("\n[BOOT] Desk 3 starting...");

  wifiSetup(WIFI_CONFIG);
mqttSetup();
  mqttClient().setCallback(mqttCallback); 

  setupOTA();
}

void loop() {
  wifiLoop();

  if (wifiIsConnected()) {
    bool justConnected = mqttEnsureConnected();
    if (justConnected) {
      onConnectPublish();
  } }

  mqttLoop();
  loopOTA();
}