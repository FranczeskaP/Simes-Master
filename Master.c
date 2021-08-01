#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include "Modbus.h"
#include "Decoder.h"
#include "PostData.h"
#include "cJSON.h"

static uint8_t schedulerCalled = 0u;
uint16_t rxData[11];
DecodedData_t decodedData[numOfSlaves];

static void SchedulerCalled(int signum);
static char * CreateStringToBePosted(DecodedData_t decodedData[numOfSlaves]);

int main()
{
    uint8_t readError = 0u;
    signal(SIGALRM, SchedulerCalled);
    alarm(5);
    ModbusInit();
    (void)ModbusReadData(modbusSensors[0].slaveNum);
    InitCurl();
    while(1)
    {
        if(1u == schedulerCalled)
        {
            schedulerCalled = 0u;
            readError = ModbusReadData(modbusSensors[0].slaveNum);
            if(0u == readError)
            {
                DecodeModbus(modbusSensors[0].receivedData, &decodedData[0]);
                PerformPost(CreateStringToBePosted(decodedData));
            }
        }
        else
        {
            printf(".\n");
        }
        sleep(1);
    }
    ModbusDeInit();
    DeInitCurl();

    return 0;
}


static void SchedulerCalled(int signum)
{
    schedulerCalled = 1u;
    alarm(5);
}

static char * CreateStringToBePosted(DecodedData_t decodedData[numOfSlaves])
{
    char *slaveName[2*numOfSlaves] = {"sensor1", "sensor2"};
    uint16_t slaveNameNum = 0u;
    cJSON *data = cJSON_CreateObject();
    for(int i = 0; i<2; i++)
    {
        cJSON *sensor0 = cJSON_AddObjectToObject(data, slaveName[slaveNameNum]) ;
        if (sensor0 == NULL)
        {
            goto end;
        }
        slaveNameNum++;

        if (cJSON_AddNumberToObject(sensor0, "voltage", decodedData[i].voltage1) == NULL)
        {
            goto end;
        }
        if (cJSON_AddNumberToObject(sensor0, "current", decodedData[i].current1) == NULL)
        {
            goto end;
        }
        if (cJSON_AddNumberToObject(sensor0, "power", decodedData[i].power1) == NULL)
        {
            goto end;
        }
        if (cJSON_AddNumberToObject(sensor0, "energy", 126) == NULL)
        {
            goto end;
        }
        if (cJSON_AddNumberToObject(sensor0, "charge_cycles", 4) == NULL)
        {
            goto end;
        }
        if (cJSON_AddNumberToObject(sensor0, "temperature", decodedData[i].temperature) == NULL)
        {
            goto end;
        }
        if (cJSON_AddNumberToObject(sensor0, "status", 1) == NULL)
        {
            goto end;
        }
        if (cJSON_AddNumberToObject(sensor0, "error", 0) == NULL)
        {
            goto end;
        }

        cJSON *sensor1 = cJSON_AddObjectToObject(data, slaveName[slaveNameNum]) ;
        if (sensor1 == NULL)
        {
            goto end;
        }
        slaveNameNum++;
        if (cJSON_AddNumberToObject(sensor1, "voltage", decodedData[i].voltage2) == NULL)
        {
            goto end;
        }
        if (cJSON_AddNumberToObject(sensor1, "current", decodedData[i].current2) == NULL)
        {
            goto end;
        }
        if (cJSON_AddNumberToObject(sensor1, "power", decodedData[i].power2) == NULL)
        {
            goto end;
        }
        if (cJSON_AddNumberToObject(sensor1, "energy", 25) == NULL)
        {
            goto end;
        }
        if (cJSON_AddNumberToObject(sensor1, "charge_cycles", 5) == NULL)
        {
            goto end;
        }
        if (cJSON_AddNumberToObject(sensor1, "temperature", decodedData[i].temperature) == NULL)
        {
            goto end;
        }
        if (cJSON_AddNumberToObject(sensor1, "status", 1) == NULL)
        {
            goto end;
        }
        if (cJSON_AddNumberToObject(sensor1, "error", 0) == NULL)
        {
            goto end;
        }
    }
    char *string = cJSON_Print(data);
    if (string == NULL)
    {
        fprintf(stderr, "Failed to print data.\n");
    }

end:
    cJSON_Delete(data);
    return string;
}
