#include "wifi.h"
#include "ntpServer.h"
#include "wifiConfigs.h"

const char* ssid = WIFI_NAME;
const char* password = WIFI_PASSWORD;
uint8_t wifi_is_connected = 0;
SemaphoreHandle_t xMutexWifiState;

uint64_t uuid;


void change_wifi_connection_state(uint8_t state) {
  xSemaphoreTake(xMutexWifiState, portMAX_DELAY);
  wifi_is_connected = state;
  xSemaphoreGive(xMutexWifiState);
}


uint8_t get_wifi_connection_state() {
  xSemaphoreTake(xMutexWifiState, portMAX_DELAY);
  uint8_t state = wifi_is_connected;
  xSemaphoreGive(xMutexWifiState);
  return state;
}


uint64_t macAddressStrToUint64(String mac_address) {
  char* endPtr;
  return strtoull(mac_address.c_str(), &endPtr, 16);
}


void connectWiFi() {
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  change_wifi_connection_state(CONNECTED);
  Serial.println("Connected!");
  iniciateNtpServer();
}


void taskWifi(void* parameters) {
  Serial.println("TaskWifi Iniciada");
  String mac_address = WiFi.macAddress();
  mac_address.replace(":", "");
  uuid = macAddressStrToUint64(mac_address);
  Serial.println(uuid);
  WiFi.begin(ssid, password);
  for (;;) {
    if (WiFi.status() != WL_CONNECTED) {
      change_wifi_connection_state(NO_CONNECTION);
      Serial.println("No Connection Wifi...");
      connectWiFi();
    }
    delay(5000);
  }
}
