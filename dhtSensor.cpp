#include "dhtSensor.h"
#include "ntpServer.h"
#include "wifi.h"
#include "mqtt.h"
#include "json.h"

#define DHTPIN 4
#define DHTTYPE DHT11


DHT dhtSensor(DHTPIN, DHTTYPE);
time_t datetime;


void getTemperature() {
  Package_T packet;
  packet.type = TEMPERATURE;
  packet.value = dhtSensor.readTemperature();
  packet.unx = (uint32_t)datetime;
  String json = createPacketJson(packet.unx, packet.type, packet.value);
  publishMessage(json);
}


void getHumidity() {
  Package_T packet;
  packet.type = HUMIDITY;
  packet.value = dhtSensor.readHumidity();
  packet.unx = (uint32_t)datetime;
  String json = createPacketJson(packet.unx, packet.type, packet.value);
  publishMessage(json);
}


void taskDhtSensor(void* parameters) {
  delay(10000);
  Serial.println("\nTaskDhtSensor Iniciada");
  dhtSensor.begin();
  for (;;) {
    time(&datetime);
    if ((datetime % 600) == 0 && get_wifi_connection_state() == CONNECTED) {
      getTemperature();
      getHumidity();
      delay(1000);
    }
    delay(10);
  }
}
