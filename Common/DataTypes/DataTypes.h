#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include <stdbool.h>
#include <stdint.h>
#include <modbus.h>

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

typedef enum
{
    StateSupport = 0,
    StateTotalForwardActiveEnergy,
    StateTotalReverseActiveEnergy,
    StateTotalForwardActiveEnergyBalanced,
    StateTotalReverseActiveEnergyBalanced,
    Phases1TotalForwardActiveEnergy,
    Phases1TotalReverseActiveEnergy,
    Phases1TotalForwardActiveEnergyBalanced,
    Phases1TotalReverseActiveEnergyBalanced,
    Phases1Frequency, 
    Phases1Voltage,
    Phases1Current,
    Phases1PowerActive,
    Phases1PowerReactive,
    Phases1POwerApparent,
    Phases1PowerFactor,
    Phases1PhaseAngle,
    Phases2TotalForwardActiveEnergy,
    Phases2TotalReverseActiveEnergy,
    Phases2TotalForwardActiveEnergyBalanced,
    Phases2TotalReverseActiveEnergyBalanced,
    Phases2Frequency,
    Phases2Voltage,
    Phases2Current,
    Phases2PowerActive,
    Phases2PowerReactive,
    Phases2POwerApparent,
    Phases2PowerFactor,
    Phases2PhaseAngle,
    Phases3TotalForwardActiveEnergy,
    Phases3TotalReverseActiveEnergy,
    Phases3TotalForwardActiveEnergyBalanced,
    Phases3TotalReverseActiveEnergyBalanced,
    Phases3Frequency,
    Phases3Voltage,
    Phases3Current,
    Phases3PowerActive,
    Phases3PowerReactive,
    Phases3POwerApparent,
    Phases3PowerFactor,
    Phases3PhaseAngle,
    TotalNumOfZamelTopics
}ZamelTopicsNums;

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

typedef struct
{
    double voltage1Rms;
    double voltage2Rms;
    double voltage3Rms;
    double current1Rms;
    double current2Rms;
    double current3Rms;
    double pPower;
    double qPower;
    double sPower;
    double pEnergy;
    double qEnergy;
    double currentThd;
    double voltageThd;
    double powerCos;
    double frequence;
    uint16_t status;
}AcDecodedData_t;

extern MqttStruct_t DcSensor1[TotalNumOfDcSensorTopics];
extern MqttStruct_t DcSensor2[TotalNumOfDcSensorTopics];
extern MqttStruct_t DcSensor3[TotalNumOfDcSensorTopics];
extern MqttStruct_t DcSensor4[TotalNumOfDcSensorTopics];
extern MqttStruct_t DcSensor5[TotalNumOfDcSensorTopics]; 

typedef struct 
{
    uint16_t slaveNum;
    CommunicationProtocols_e communicationProtocol;
    MqttStruct_t dcSensorMqttData[TotalNumOfDcSensorTopics];
	char * mqttReceivedData[TotalNumOfDcSensorTopics];
    bool allTopicsUpdated;
    modbus_t *slave;
    uint16_t modbusReceivedData[18];
    DcDecodedData_t dcDecodedDataCh1;
    DcDecodedData_t dcDecodedDataCh2;
    bool updated;
}DcSensorData_t;

typedef struct 
{
    uint16_t slaveNum;
    CommunicationProtocols_e communicationProtocol;
    MqttStruct_t acSensorMqttData[TotalNumOfZamelTopics];
	char * mqttReceivedData[TotalNumOfZamelTopics];
    bool allTopicsUpdated;
    modbus_t *slave;
    uint16_t modbusReceivedData[18];
    AcDecodedData_t acDecodedData;
    bool updated;
}AcSensorData_t;

extern DcSensorData_t DcSensorData[numOfDcSlaves];
extern AcSensorData_t AcSensorData;

#endif