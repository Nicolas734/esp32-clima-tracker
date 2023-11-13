#ifndef __JSON_H__
#define __JSON_H__ 1

#include <ArduinoJson.h>

String createPacketJson(uint64_t uid, uint32_t unx, uint8_t type, float value);

#endif
