#include "wifi.h"


TaskHandle_t tTaskWifi;

void setup() {
  Serial.begin(115200);

  xTaskCreatePinnedToCore(
    taskWifi,    //function name
    "tTaskWifi",  //task name
    10000,           // task stack size
    NULL,            // task parameters
    1,               // task priority
    &tTaskWifi,         // task handle
    0);              //task core - loop run on core 1
  delay(100);

}

void loop() {
  // put your main code here, to run repeatedly:
}
