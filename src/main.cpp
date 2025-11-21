#include <Arduino.h>
#include <Wire.h>

#include "WifiConnect.h"
#include "OTA.h"
#include "MqttClient.h"
#include "MqttTemplates.h"
#include "sht31.h"
#include "ServoMotor.h"

#include "ProjectProfile.h"
#include "ProjectConfig.h"
#include "SensorProfile.h"
#include "Topics.h"

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  String t(topic);
  String msg;
  msg.reserve(length + 1);
  for (unsigned int i = 0; i < length; i++) {
    msg += (char)payload[i];
  }

  if (t == Topics::servoCommand()) {
    int angle = msg.toInt();
    Serial.printf("[MQTT][SERVO] Commande angle: %d\n", angle);
    servoSetTargetAngle(angle);

    // Publier l'état actuel
    if (wifiIsConnected() && mqttClient().connected()) {
      char buf[8];
      snprintf(buf, sizeof(buf), "%d", servoCurrentAngle());
      mqttClient().publish(
        Topics::servoState().c_str(),
        buf,
        true
      );
    }
    return;
  }

  Serial.printf("[MQTT] Message recu sur le topic %s: ", topic);
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void onConnectPublish() {
  mqttPublishDiscovery();
  mqttClient().subscribe(Topics::servoCommand().c_str());
  Serial.printf("[MQTT] Subscribed to %s\n", Topics::servoCommand().c_str());
}

void onSht31Measurement(float temperature, float humidity) {
  mqttPublishSht(temperature, humidity);
}

void setup() {
  Serial.begin(115200);
  uint32_t t0 = millis();
  while (!Serial && millis() - t0 < 3000) { delay(10); }

  Serial.printf("\n[BOOT] %s starting...\n", ProjectConfig::deviceName());

  // WiFi
  WifiConfig wifiCfg {
    .ssid     = ProjectConfig::wifiSsid(),
    .password = ProjectConfig::wifiPass(),
    .localIP  = ProjectConfig::wifiLocalIP(),
    .gateway  = ProjectConfig::wifiGateway(),
    .subnet   = ProjectConfig::wifiSubnet(),
    .dns1     = ProjectConfig::wifiDns1(),
    .dns2     = ProjectConfig::wifiDns2(),
    .hostname = ProjectConfig::wifiHostname()
  };

  wifiSetup(wifiCfg);

  mqttSetup();
  mqttClient().setCallback(mqttCallback);

  Sht31Config cfg {
    .sdaPin     = SensorProfile::I2C_SDA,
    .sclPin     = SensorProfile::I2C_SCL,
    .intervalMs = SensorProfile::SHT31_INTERVAL_MS
  };
  sht31Setup(cfg, onSht31Measurement);


  ServoConfig servoCfg {
    .pin      = SensorProfile::SERVO_PIN,
    .minAngle = SensorProfile::SERVO_MIN_ANGLE,
    .maxAngle = SensorProfile::SERVO_MAX_ANGLE,
    .minUs    = 500,   // valeurs usuelles SG90, tu peux ajuster
    .maxUs    = 2400
  };
  servoSetup(servoCfg);

  setupOTA();
}

void loop() {
  wifiLoop();

  if (wifiIsConnected()) {
    bool justConnected = mqttEnsureConnected();
    if (justConnected) {
      onConnectPublish();
    }
  }

  sht31Loop();
  servoLoop();
  mqttLoop();
  loopOTA();
}
