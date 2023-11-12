#include "wifi.h"
#include "ntpServer.h"

const char* ssid = "nicolas";    //ADICIONE NO LUGAR DE "Fatec WiFi" A SUA REDE
const char* password = "29072003";  // ADICIONE SUA SENHA
uint8_t wifi_is_connected = 0;
SemaphoreHandle_t xMutexWifiState;


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


void connectWiFi() {
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  change_wifi_connection_state(1);
  Serial.println("Connected!");
  iniciateNtpServer();
}


void taskWifi(void* parameters) {
  Serial.println("TaskWifi Iniciada");
  WiFi.begin(ssid, password);
  for (;;) {
    if (WiFi.status() != WL_CONNECTED) {
      change_wifi_connection_state(0);
      Serial.println("No Connection Wifi...");
      connectWiFi();
    }
    delay(5000);
  }
}
