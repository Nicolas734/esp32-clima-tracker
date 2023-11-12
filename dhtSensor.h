#ifndef __DHT_SENSOR_H__
#define __DHT_SENSOR_H__ 1

#include <DHT.h>

//extern DHT dhtSensor;
enum PACKET_TYPE{
  TEMPERATURE = 1,
  HUMIDITY = 2
};

typedef struct {
  uint32_t unx;
  float value;
  uint8_t type;
} Package_T;

void taskDhtSensor(void* parameters);

#endif
