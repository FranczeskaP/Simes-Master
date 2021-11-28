#ifndef MY_CONFIG_H
#define MY_CONFIG_H

#include <stdbool.h>
#include <stdint.h>
#include "DataTypes.h"

typedef struct{
    char * SensorId;
    char * CommunicationMetod;
}ConfigParams_t;

extern ConfigParams_t configuration[MAX_NUM_OF_SENSORS];

void GetConfigurationData(void);
void ProcessConfigData(void);
void InitConfigData(void);

#endif
