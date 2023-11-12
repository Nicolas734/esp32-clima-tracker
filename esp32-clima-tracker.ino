#include "wifi.h"
#include "dhtSensor.h"

TaskHandle_t tTaskWifi;
TaskHandle_t tTaskDhtSensor;

void setup() {
  Serial.begin(115200);

  xMutexWifiState = xSemaphoreCreateMutex();
  if (xMutexWifiState != NULL) {
    Serial.printf("xMutexWifiState criado!\n");
  }
  
  xTaskCreatePinnedToCore(
    taskWifi,    // função
    "tTaskWifi",  // nome da tarefa
    5000,           // tamanho da pilha da tarefa
    NULL,            // parâmetros da tarefa
    1,               // prioridade da tarefa
    &tTaskWifi,         // handle da tarefa
    0);              // núcleo da tarefa
  delay(100);

  xTaskCreatePinnedToCore(
    taskDhtSensor,    //function name
    "tTaskDhtSensor",  //task name
    5000,           // task stack size
    NULL,            // task parameters
    1,               // task priority
    &tTaskDhtSensor,         // task handle
    0);              //task core - loop run on core 1
  delay(100);
}

void loop() {
  // Seu código principal aqui
}
