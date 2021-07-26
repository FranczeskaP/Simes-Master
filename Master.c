#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <unistd.h>
#include "Modbus.h"
#include "Decoder.h"
#include "PostData.h"

static uint8_t schedulerCalled = 0u;
uint16_t rxData[11];
DecodedData_t decodedData[numOfSlaves];

static void SchedulerCalled(int signum);

int main()
{
    signal(SIGALRM, SchedulerCalled);
    alarm(5);
    ModbusInit();
    InitCurl();
    while(1)
    {
        if(1u == schedulerCalled)
        {
            schedulerCalled = 0u;
            ModbusReadData(modbusSensors[0].slaveNum);
            DecodeModbus(modbusSensors[0].receivedData, &decodedData[0]);
            PerformPost(&decodedData);
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
