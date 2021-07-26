#include <stdio.h>
#include <stdint.h>
#include <signal.h>
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
    cJSON *data = cJSON_CreateObject();
    cJSON *sensor1 = cJSON_AddObjectToObject(data, "sensor1") ;

    if (sensor1 == NULL)
    {
        goto end;
    }

    if (cJSON_AddNumberToObject(sensor1, "voltage", decodedData[0].voltage1) == NULL)
    {
        goto end;
    }
    if (cJSON_AddNumberToObject(sensor1, "current", decodedData[0].current1) == NULL)
    {
        goto end;
    }
    if (cJSON_AddNumberToObject(sensor1, "power", decodedData[0].power1) == NULL)
    {
        goto end;
    }
    if (cJSON_AddNumberToObject(sensor1, "energy", decodedData[0].power2) == NULL)
    {
        goto end;
    }
    if (cJSON_AddNumberToObject(sensor1, "charge_cycles", decodedData[0].voltage2) == NULL)
    {
        goto end;
    }
    if (cJSON_AddNumberToObject(sensor1, "temperature", decodedData[0].temperature) == NULL)
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
    cJSON *sensor2 = cJSON_AddObjectToObject(data, "sensor2") ;
    if (sensor2 == NULL)
    {
        goto end;
    }

    if (cJSON_AddNumberToObject(sensor2, "voltage", decodedData[0].voltage1) == NULL)
    {
        goto end;
    }
    if (cJSON_AddNumberToObject(sensor2, "current", decodedData[0].current1) == NULL)
    {
        goto end;
    }
    if (cJSON_AddNumberToObject(sensor2, "power", decodedData[0].power1) == NULL)
    {
        goto end;
    }
    if (cJSON_AddNumberToObject(sensor2, "energy", decodedData[0].power2) == NULL)
    {
        goto end;
    }
    if (cJSON_AddNumberToObject(sensor2, "charge_cycles", decodedData[0].voltage2) == NULL)
    {
        goto end;
    }
    if (cJSON_AddNumberToObject(sensor2, "temperature", decodedData[0].temperature) == NULL)
    {
        goto end;
    }
    if (cJSON_AddNumberToObject(sensor2, "status", 0) == NULL)
    {
        goto end;
    }
    if (cJSON_AddNumberToObject(sensor2, "error", 1) == NULL)
    {
        goto end;
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
