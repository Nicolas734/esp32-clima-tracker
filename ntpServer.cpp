#include "ntpServer.h"
#include "wifi.h"


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
  time_t timeNow;
  time(&timeNow);
  tm *date = gmtime(&timeNow); 
  //Serial.print("Time Now: ");Serial.print(timeNow);
  Serial.print("Connect to NTP Server in ");
  Serial.print(date);
}
