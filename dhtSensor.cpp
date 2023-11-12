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


void taskDhtSensor(void* parameters) {
  delay(10000);
  Serial.println("\nTaskDhtSensor Iniciada");
  DHT dhtSensor(DHTPIN, DHTTYPE);
  dhtSensor.begin();
  time_t datetime;
  for (;;) {
    time(&datetime);
    if ((datetime % 60) == 0 && get_wifi_connection_state() == 1) {
      Package_T packet;
      packet.type = 1;
      packet.value = dhtSensor.readTemperature();
      packet.unx = (uint32_t)datetime;
      Serial.println(packet.type);
      Serial.println(packet.value);
      Serial.println(packet.unx);
      delay(1000);
    }
    delay(10);
  }
}
