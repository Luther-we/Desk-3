#include "WifiConnect.h"

static WifiConfig    g_cfg;
static bool          g_initialized = false;
static unsigned long g_lastAttempt = 0;
static const unsigned long RECONNECT_INTERVAL = 15000; // 15 s

bool wifiIsConnected() {
  return WiFi.status() == WL_CONNECTED;
}

void wifiSetup(const WifiConfig& cfg) {
  g_cfg = cfg;
  g_initialized = true;

  Serial.println("[WiFi] Initialisation...");

  if (!WiFi.config(g_cfg.localIP, g_cfg.gateway, g_cfg.subnet, g_cfg.dns1, g_cfg.dns2)) {
    Serial.println("[WiFi] Erreur de configuration IP");
  }

  if (g_cfg.hostname && strlen(g_cfg.hostname) > 0) {
    WiFi.setHostname(g_cfg.hostname);
  }

  WiFi.begin(g_cfg.ssid, g_cfg.password);
  g_lastAttempt = millis();
}

void wifiLoop() {
  if (!g_initialized) return;

  if (wifiIsConnected()) {
    static bool firstConnectLog = true;
    if (firstConnectLog) {
      Serial.print("[WiFi] Connecte: ");
      Serial.println(WiFi.localIP());
      firstConnectLog = false;
    }
    return;
  }

  static bool firstDisconnectLog = true;
  if (firstDisconnectLog) {
    Serial.println("[WiFi] Deconnecte, tentative de reconnexion...");
    firstDisconnectLog = false;
  }

  unsigned long now = millis();
  if (now - g_lastAttempt > RECONNECT_INTERVAL) {
    Serial.printf("[WiFi] Nouvelle tentative vers %s...\n", g_cfg.ssid);
    WiFi.disconnect();
    WiFi.begin(g_cfg.ssid, g_cfg.password);
    g_lastAttempt = now;
  }
}
