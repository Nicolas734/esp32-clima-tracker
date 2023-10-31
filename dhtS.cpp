#include "dhtS.h"

#define DHTPIN 4
#define DHTTYPE DHT11


void taskDhtSensor(void* parameters) {
  DHT dhtSensor(DHTPIN, DHTTYPE);
  dhtSensor.begin();
  for (;;) {
    float t = dhtSensor.readTemperature();
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print("\n");
    delay(3000);
  }
}
