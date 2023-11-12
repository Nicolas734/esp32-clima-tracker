#include "json.h"


StaticJsonDocument<200> doc;


String createPacketJson(uint32_t unx, uint8_t type, float value) {
  doc["unx"] = unx;
  doc["value"] = value;
  doc["type"] = type;
  String jsonString;
  if (serializeJson(doc, jsonString) == 0) {
    jsonString = "{}";
    Serial.println("Erro durante a serialização JSON");
  }
  return jsonString;
}
