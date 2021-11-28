#include <string.h>
#include <stdlib.h>
#include "Configuration.h"
#include "csvparser.h"

ConfigParams_t configuration[MAX_NUM_OF_SENSORS];

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
    for(uint8_t i = 0u; i < numOfDcSlaves; i++)
    {
        DcSensorData[i].slaveNum = (uint16_t)atoi(configuration[i].SensorId);

        if(0 == strcmp(configuration[i].CommunicationMetod, "Modbus"))
        {
            DcSensorData[i].communicationProtocol = Modbus;
        }
        else if(0 == strcmp(configuration[i].CommunicationMetod,  "Mqtt"))
        {
            DcSensorData[i].communicationProtocol = Mqtt;
        }

    }

    for(uint8_t i = 0u; i < numOfDcSlaves; i++)
    {
        printf("Id: %i\n", DcSensorData[i].slaveNum);
        printf("ComProt: %i\n", DcSensorData[i].communicationProtocol);
    }

}

void InitConfigData(void)
{
    for(uint8_t i = 0u; i < MAX_NUM_OF_SENSORS; i++)
    {
        configuration[i].SensorId = malloc(64 * sizeof(char));
        configuration[i].CommunicationMetod = malloc(64 * sizeof(char));
    }
}
