#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include <stdbool.h>
#include <stdint.h>

typedef enum
{
    slave0 = 0u,
    slave1 = 1u,
    slave2 = 2u,
    slave3 = 3u,
    slave4 = 4u,
    numOfDcSlaves
}DcSlaves;


typedef enum{
    None,
    Mqtt,
    Modbus
}CommunicationProtocols_e;

typedef struct
{
    char *topic;
    bool topicUpdated;
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

typedef struct
{
    double temperature;
    double voltage;
    double current;
    double power;
    uint16_t efficiency;
    double electricCharge;
    double energy;
}DcDecodedData_t;

extern MqttStruct_t DcSensor1[TotalNumOfDcSensorTopics];
extern MqttStruct_t DcSensor2[TotalNumOfDcSensorTopics];
extern MqttStruct_t DcSensor3[TotalNumOfDcSensorTopics];
extern MqttStruct_t DcSensor4[TotalNumOfDcSensorTopics];
extern MqttStruct_t DcSensor5[TotalNumOfDcSensorTopics]; 

typedef struct 
{
    uint16_t slaveNum;
    CommunicationProtocols_e communicationProtocol;
    MqttStruct_t DcSensorMqttData[TotalNumOfDcSensorTopics];
	char * mqttReceivedData[TotalNumOfDcSensorTopics];
    modbus_t *slave;
    uint16_t modbusReceivedData[18];
    DcDecodedData_t DcDecodedData;
}DcSensorData_t;

extern DcSensorData_t DcSensorData[5];

#endif