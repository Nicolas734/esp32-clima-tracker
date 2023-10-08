#include "wifi.h"

const char* ssid = "";    //ADICIONE NO LUGAR DE "Fatec WiFi" A SUA REDE
const char* password = "";  // ADICIONE SUA SENHA

void connectWiFi() {
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected!");
}


void taskWifi(void* parameters) {
  Serial.println("TaskWifi Iniciada");
  WiFi.begin(ssid, password);
  for (;;) {
    if (WiFi.status() != WL_CONNECTED){
      Serial.println("No Connection Wifi...");
      connectWiFi();
    }
    delay(5000);
  }
}
