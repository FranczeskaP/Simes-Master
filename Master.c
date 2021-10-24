#include "ModbusMaster.h"
#include "MqttMaster.h"
#include <stdio.h>
#include <string.h>
#include "csvparser.h"

#define MAX_NUM_OF_SENSORS  5u

typedef struct{
    char * SensorId;
    char * SensorName;
    char * ChannelsUsed;
    char * CommunicationMetod;
}ConfigParams;

ConfigParams configuration[MAX_NUM_OF_SENSORS];
static void GetConfigurationData(void);

int main()
{
    GetConfigurationData();
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
