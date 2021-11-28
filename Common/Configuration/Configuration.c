#include <string.h>
#include <stdlib.h>
#include "Configuration.h"
#include "csvparser.h"
#include "DataTypes.h"

ConfigParams_t configuration[MAX_NUM_OF_SENSORS];
Configuration_t configurationData[MAX_NUM_OF_SENSORS];

void GetConfigurationData(void)
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
        strcpy(configuration[i].SensorId, rowFields[0]);
        strcpy(configuration[i].CommunicationMetod, rowFields[1]);
        CsvParser_destroy_row(row);
        i++;
    }
    CsvParser_destroy(csvparser);
}

void ProcessConfigData(void)
{
    /* todo AC sensor for i = 0 */
    for(uint8_t i = 1u; i < MAX_NUM_OF_SENSORS; i++)
    {
        int id = atoi(configuration[i].SensorId);
        DcSensorData[id-1].slaveNum = id;

        if(0 == strcmp(configuration[i].CommunicationMetod, "Modbus"))
        {
            DcSensorData[id-1].communicationProtocol = Modbus;
        }
        else if(0 == strcmp(configuration[i].CommunicationMetod,  "Mqtt"))
        {
            DcSensorData[id-1].communicationProtocol = Mqtt;
        }

    }

    for(int i = 0; i < MAX_NUM_OF_SENSORS; i++)
    {
        printf("Id: %i\n", configurationData[i].id);
        printf("ComProt: %i\n", configurationData[i].communicationProtocol);
    }

}

void InitConfigData(void)
{
    for(uint8_t i = 0u; i < MAX_NUM_OF_SENSORS; i++)
    {
        configurationData[i].id = 0u;
        configurationData[i].communicationProtocol = None;
        configuration[i].SensorId = malloc(64 * sizeof(char));
        configuration[i].CommunicationMetod = malloc(64 * sizeof(char));
    }
}
