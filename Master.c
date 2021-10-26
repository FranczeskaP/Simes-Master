#include "ModbusMaster.h"
#include "MqttMaster.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "csvparser.h"

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
    CommunicationProtocols_e communicationProtocol;
}Configuration_t;

ConfigParams_t configuration[MAX_NUM_OF_SENSORS];
Configuration_t configurationData[MAX_NUM_OF_SENSORS];
static void GetConfigurationData(void);
static void ProcessConfigData(void);
static void InitConfigData(void);

int main()
{
    InitConfigData();
    GetConfigurationData();
    ProcessConfigData();
    //ModbusMainFunction();
    //MqttMainFunction();
    return 0;
}

static void GetConfigurationData(void)
{
    int i = 0;
    CsvParser *csvparser = CsvParser_new("./../config/SimesMaterConfig.csv", ",", 1);
    CsvRow *row;
    const CsvRow *header = CsvParser_getHeader(csvparser);
    const char **headerFields = CsvParser_getFields(header);
    while ((row = CsvParser_getRow(csvparser))) 
    {
        if(i >= MAX_NUM_OF_SENSORS)
        {
            printf("Too many sensors defined.\n");
            break;
        }
        const char **rowFields = CsvParser_getFields(row);
        configuration[i].SensorId = rowFields[0];
        configuration[i].SensorName = rowFields[1];
        configuration[i].ChannelsUsed = rowFields[2];
        configuration[i].CommunicationMetod = rowFields[3];
        CsvParser_destroy_row(row);
        i++;
    }
    CsvParser_destroy(csvparser);
	
    return 0;
}

static void ProcessConfigData(void)
{
    for(uint8_t i = 0u; i < MAX_NUM_OF_SENSORS; i++)
    {
        uint8_t id = (uint8_t)atoi(configuration[i].SensorId);
        configurationData[id - 1].used = true;
        configurationData[id - 1].id = id;
        if(configuration[i].ChannelsUsed == "First")
        {
            configurationData[id - 1].channel1Used = true;
            configurationData[id - 1].channel1Name = configuration[i].SensorName;
        }
        else if(configuration[i].ChannelsUsed == "Second")
        {
            configurationData[id - 1].channel2Used = true;
            configurationData[id - 1].channel2Name = configuration[i].SensorName;
        }

        if(configuration[i].CommunicationMetod == "Modbus")
        {
            configurationData[id - 1].communicationProtocol = Modbus;
        }
        else if(configuration[i].CommunicationMetod == "Mqtt")
        {
            configurationData[id - 1].communicationProtocol = Mqtt;
        }

    }

    for(int i = 0; i < MAX_NUM_OF_SENSORS; i++)
    {
        printf("Used: %B\n", configurationData[i].used);
        printf("Channel1used: %B\n", configurationData[i].channel1Used);
        printf("Channel2used: %B\n", configurationData[i].channel2Used);
        printf("Channel1Name: %s\n", configurationData[i].channel1Name);
        printf("Channel2Name: %s\n", configurationData[i].channel2Name);
        printf("ComProt: %s\n", configurationData[i].communicationProtocol);
        printf("Id: %i\n", configurationData[i].id);
    }

}

static void InitConfigData(void)
{
    for(uint8_t i = 0u; i < MAX_NUM_OF_SENSORS; i++)
    {
        configurationData[i].used = false;
        configurationData[i].id = 0u;
        configurationData[i].channel1Used = false;
        configurationData[i].channel2Used = false;
        configurationData[i].channel1Name = "";
        configurationData[i].channel2Name = "";
        configurationData[i].communicationProtocol = None;
    }
}
