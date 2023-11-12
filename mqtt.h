#ifndef __MQTT_H__
#define __MQTT_H__ 1

#include <PubSubClient.h>

extern PubSubClient client;
extern const char *mqtt_server;
extern SemaphoreHandle_t xMutexMqttPublish;

void publishMessage(String msg);
void taskMqtt(void* parameters);

#endif
