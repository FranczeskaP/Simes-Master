#ifndef POSTDATA_H
#define POSTDATA_H

#include <stdint.h>
#include "Decoder.h"
#include "MqttDefinitions.h"

extern void InitCurl(void);
extern char * CreateStringToBePostedModbus(DecodedData_t decodedData[numOfSlaves]);
extern char * CreateStringToBePostedMqtt(MqttStruct_t dcSensor1[TotalNumOfDcSensorTopics], MqttStruct_t dcSensor2[TotalNumOfDcSensorTopics],
                                         MqttStruct_t dcSensor3[TotalNumOfDcSensorTopics], MqttStruct_t dcSensor4[TotalNumOfDcSensorTopics],
                                         MqttStruct_t dcSensor5[TotalNumOfDcSensorTopics]);
extern void PerformPost(char * dataToPost);
extern void DeInitCurl(void);

#endif
