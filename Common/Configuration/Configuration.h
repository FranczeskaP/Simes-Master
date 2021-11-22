#ifndef MY_CONFIG_H
#define MY_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#define MAX_NUM_OF_SENSORS  5u

typedef struct{
    char * SensorId;
    char * SensorName;
    char * ChannelsUsed;
    char * CommunicationMetod;
}ConfigParams_t;

typedef enum{
    None,
    Mqtt,
    Modbus
}CommunicationProtocols_e;

typedef struct{
    bool used;
    uint8_t id;
    bool channel1Used;
    char * channel1Name;
    bool channel2Used;
    char * channel2Name;
    bool acSensor;
    char * acSensorName;
    CommunicationProtocols_e communicationProtocol;
}Configuration_t;

extern ConfigParams_t configuration[MAX_NUM_OF_SENSORS];
extern Configuration_t configurationData[MAX_NUM_OF_SENSORS];

void GetConfigurationData(void);
void ProcessConfigData(void);
void InitConfigData(void);

#endif
