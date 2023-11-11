#include "dhtSensor.h"

#define DHTPIN 4
#define DHTTYPE DHT11

typedef struct {
  uint32_t unx;
  float value;
  uint8_t type;
} Package_T;


void taskDhtSensor(void* parameters) {
  DHT dhtSensor(DHTPIN, DHTTYPE);
  dhtSensor.begin();
  for (;;) {
    Package_T packet;
    packet.type = 1;
    packet.value = dhtSensor.readTemperature();
    packet.unx = 0;
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print("\n");
    delay(3000);
  }
}
