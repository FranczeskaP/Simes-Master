#ifndef MQTT_DEFINITIONS_H
#define MQTT_DEFINITIONS_H
#include <stdbool.h>

typedef struct
{
    char *topic;
    bool topicUpdated;
	char *data;
}MqttStruct_t;

typedef enum
{
	Ch1 = 0,
	Ch2,
	Ch3,
	Ch4,
	Eff,
	P1,
	P2,
	EnergyCh1,
	EnergyCh2,
	QCh1,
	QCh2,
	Temp,
	TotalNumOfDcSensorTopics
}DcSensorsTopicsNums;

extern MqttStruct_t DcSensor1[TotalNumOfDcSensorTopics];
extern MqttStruct_t DcSensor2[TotalNumOfDcSensorTopics];
extern MqttStruct_t DcSensor3[TotalNumOfDcSensorTopics];
extern MqttStruct_t DcSensor4[TotalNumOfDcSensorTopics];
extern MqttStruct_t DcSensor5[TotalNumOfDcSensorTopics];

#endif
