#include "mqtt.h"
#include "wifi.h"
#include "mqttConfig.h"



const char *mqtt_broker = MQTT_BROKER;
const char *mqtt_topic = MQTT_TOPIC;
const uint16_t mqtt_port = MQTT_PORT;

SemaphoreHandle_t xMutexMqttPublish;

WiFiClient espClient;
PubSubClient client(espClient);


void reconnect() {
  while (!client.connected()) {
    Serial.println("Tentando conectar ao MQTT...");
    String client_id = "esp32-client-";
    client_id += String(WiFi.macAddress());
    if (client.connect(client_id.c_str())) {
      Serial.println("Conectado ao MQTT");
    } else {
      Serial.print("Falha na conexão. Retornando em 5 segundos...");
      delay(5000);
    }
  }
}



void publishMessage(String msg) {
  xSemaphoreTake(xMutexMqttPublish, portMAX_DELAY);
  client.publish(mqtt_topic, msg.c_str());
  xSemaphoreGive(xMutexMqttPublish);
}


void taskMqtt(void* parameters) {
  delay(10000);
  Serial.println("\nTaskQtt Iniciada");
  client.setServer(mqtt_broker, mqtt_port);
  for (;;) {
    if (!client.connected()) {
      reconnect();
    }
    client.loop();
    delay(5000);
  }
  delay(10);
}
