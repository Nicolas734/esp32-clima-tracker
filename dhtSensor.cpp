#include "dhtSensor.h"
#include "ntpServer.h"
#include "wifi.h"

#define DHTPIN 4
#define DHTTYPE DHT11

typedef struct {
  uint32_t unx;
  float value;
  uint8_t type;
} Package_T;

DHT dhtSensor(DHTPIN, DHTTYPE);
time_t datetime;


void getTemperature() {
  Package_T packet;
  packet.type = TEMPERATURE;
  packet.value = dhtSensor.readTemperature();
  packet.unx = (uint32_t)datetime;
  Serial.println(packet.type);
  Serial.println(packet.value);
  Serial.println(packet.unx);
}


void getHumidity() {
  Package_T packet;
  packet.type = HUMIDITY;
  packet.value = dhtSensor.readHumidity();
  packet.unx = (uint32_t)datetime;
  Serial.println(packet.type);
  Serial.println(packet.value);
  Serial.println(packet.unx);
}


void taskDhtSensor(void* parameters) {
  delay(10000);
  Serial.println("\nTaskDhtSensor Iniciada");
  dhtSensor.begin();
  for (;;) {
    time(&datetime);
    if ((datetime % 60) == 0 && get_wifi_connection_state() == CONNECTED) {
      getTemperature();
      getHumidity();
      delay(1000);
    }
    delay(10);
  }
}
