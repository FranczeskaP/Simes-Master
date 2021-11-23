#ifndef MQTT_MASTER_H
#define MQTT_MASTER_H

#include "MqttDefinitions.h"

extern void MqttInit(void);
extern void ReadMqtt(void);
extern bool CheckIfAllUpdated(void);

#endif
