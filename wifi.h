#ifndef __WIFI_W_H__
#define __WIFI_W_H__ 1

#include <WiFi.h>

void connectWiFi();
void taskWifi(void *parameters);
void change_wifi_connection_state(uint8_t state);
uint8_t get_wifi_connection_state();

extern SemaphoreHandle_t xMutexWifiState;

#endif
