#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#define NUM_OF_DC_REGISTERS  (18u)
#define NUM_OF_AC_SENSORS   1u

typedef enum
{
    slave0 = 0u,
    slave1 = 1u,
    slave2 = 2u,
    slave3 = 3u,
    slave4 = 4u,
    numOfDcSlaves
}DcSlaves;

#define MAX_NUM_OF_SENSORS  ((uint8_t)numOfDcSlaves + NUM_OF_AC_SENSORS)

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
    bool allTopicsUpdated;
    modbus_t *slave;
    uint16_t modbusReceivedData[18];
    DcDecodedData_t dcDecodedDataCh1;
    DcDecodedData_t dcDecodedDataCh2;
}DcSensorData_t;

extern DcSensorData_t DcSensorData[numOfDcSlaves];

#endif