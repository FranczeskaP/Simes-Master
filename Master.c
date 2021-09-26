#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "Modbus.h"
#include "Decoder.h"
#include "PostData.h"
#include "cJSON.h"
#include "Mqtt.h"

#define TIME_MS     (2u)

static uint8_t schedulerCalled = 0u;
uint16_t rxData[11];
DecodedData_t decodedData[numOfSlaves];
struct timespec WaitTime = {
    .tv_sec = 0,
    .tv_nsec = TIME_MS * 1000000,
};

static void SchedulerCalled(int signum);
static char * CreateStringToBePosted(DecodedData_t decodedData[numOfSlaves]);

int main()
{
    uint8_t switchToMqtt = 0u;
    signal(SIGALRM, SchedulerCalled);
    alarm(5);
    ModbusInit();
    (void)ModbusReadData(modbusSensors[0].slaveNum);
    (void)ModbusReadData(modbusSensors[1].slaveNum);
    InitCurl();
    while(1)
    {
        if(1u == schedulerCalled)
        {
            uint8_t readError = 0u;
            schedulerCalled = 0u;
            for(uint8_t i = 0u; i < numOfSlaves; i++)
            {
                readError |= ModbusReadData(modbusSensors[i].slaveNum);
                nanosleep(&WaitTime, &WaitTime);
            }
            if(0u == readError)
            {
                switchToMqtt = 0u;
                for(uint8_t i = 0u; i < numOfSlaves; i++)
                {
                    DecodeModbus(modbusSensors[i].receivedData, &decodedData[i]);
                }
                PerformPost(CreateStringToBePosted(decodedData));
                // printf("%f\n", decodedData[0].current1);
                // printf("%f\n", decodedData[0].current2);
                // printf("%u\n", decodedData[0].efficiency);
                // printf("%f\n", decodedData[0].electricCharge1);
                // printf("%f\n", decodedData[0].electricCharge2);
                // printf("%f\n", decodedData[0].energy1);
                // printf("%f\n", decodedData[0].energy2);
                // printf("%f\n", decodedData[0].power1);
                // printf("%f\n", decodedData[0].power2);
                // printf("%f\n", decodedData[0].temperature);
                // printf("%f\n", decodedData[0].voltage1);
                // printf("%f\n", decodedData[0].voltage2);
                // printf("\n");
                // printf("\n");
                // printf("%f\n", decodedData[1].current1);
                // printf("%f\n", decodedData[1].current2);
                // printf("%u\n", decodedData[1].efficiency);
                // printf("%f\n", decodedData[1].electricCharge1);
                // printf("%f\n", decodedData[1].electricCharge2);
                // printf("%f\n", decodedData[1].energy1);
                // printf("%f\n", decodedData[1].energy2);
                // printf("%f\n", decodedData[1].power1);
                // printf("%f\n", decodedData[1].power2);
                // printf("%f\n", decodedData[1].temperature);
                // printf("%f\n", decodedData[1].voltage1);
                // printf("%f\n", decodedData[1].voltage2);
            }
            else
            {
                switchToMqtt++;
            }
        }
        else
        {
            printf(".\n");
        }
        sleep(1);
        if(5u == switchToMqtt)
        {
            ModbusDeInit();
            DeInitCurl();
            SwitchToMqtt();
        }
    }

    return 0;
}


static void SchedulerCalled(int signum)
{
    schedulerCalled = 1u;
    alarm(5);
}

static char * CreateStringToBePosted(DecodedData_t decodedData[numOfSlaves])
{
    char *slaveName[2*numOfSlaves] = {"sensor1", "sensor2", "sensor3", "sensor4", "sensor5",
                                      "sensor6", "sensor7", "sensor8", "sensor9", "sensor10"};
    uint16_t slaveNameNum = 0u;
    cJSON *data = cJSON_CreateObject();
    for(int i = 0; i<numOfSlaves; i++)
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
        if (cJSON_AddNumberToObject(sensor0, "energy", decodedData[i].energy1) == NULL)
        {
            goto end;
        }
        if (cJSON_AddNumberToObject(sensor0, "charge_cycles", decodedData[i].electricCharge1) == NULL)
        {
            goto end;
        }
        if (cJSON_AddNumberToObject(sensor0, "temperature", decodedData[i].temperature) == NULL)
        {
            goto end;
        }
        if (cJSON_AddNumberToObject(sensor0, "status", decodedData[i].efficiency) == NULL)
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
        if (cJSON_AddNumberToObject(sensor1, "energy", decodedData[i].energy2) == NULL)
        {
            goto end;
        }
        if (cJSON_AddNumberToObject(sensor1, "charge_cycles", decodedData[i].electricCharge2) == NULL)
        {
            goto end;
        }
        if (cJSON_AddNumberToObject(sensor1, "temperature", decodedData[i].temperature) == NULL)
        {
            goto end;
        }
        if (cJSON_AddNumberToObject(sensor1, "status", decodedData[i].efficiency) == NULL)
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
