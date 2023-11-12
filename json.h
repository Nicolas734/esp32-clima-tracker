#ifndef __JSON_H__
#define __JSON_H__ 1

#include <ArduinoJson.h>

String createPacketJson(uint32_t unx, uint8_t type, float value);

#endif
