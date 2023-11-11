#include "ntpServer.h"

const char* ntpServer = "br.pool.ntp.org";
const long gmtOffset = 0;
const int daylight = 0;


time_t datetime;
time_t adjustedTime;
struct tm timeinfo;


void iniciateNtpServer() {
  configTime(gmtOffset, daylight, ntpServer);
  Serial.println("Aguardando conexão com o NTP server");
  while (!getLocalTime(&timeinfo)) {
    Serial.println(".");
    delay(1000);
  }
  Serial.print("Conectado ao NTP Server");
}