#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <unistd.h>
#include "Modbus.h"
#include "Decoder.h"

static uint8_t schedulerCalled = 0u;
uint16_t rxData[11];
DecodedData_t decodedData;

static void SchedulerCalled(int signum);

int main()
{
    signal(SIGALRM, SchedulerCalled);
    alarm(5);
    ModbusInit();
    while(1)
    {
        if(1u == schedulerCalled)
        {
            schedulerCalled = 0u;
            ModbusReadData(modbusSensors[0].slaveNum);
            DecodeModbus(modbusSensors[0].receivedData, &decodedData);
            printf("%f\n", decodedData.temperature); 
            printf("%f\n", decodedData.voltage1); 
            printf("%f\n", decodedData.current1); 
            printf("%f\n", decodedData.voltage2); 
            printf("%f\n", decodedData.current2); 
            printf("%f\n", decodedData.power1); 
            printf("%f\n", decodedData.power2); 
        }
        else
        {
            printf(".\n");
        }
        sleep(1);
    }
    ModbusDeInit();

    return 0;
}


static void SchedulerCalled(int signum)
{
    schedulerCalled = 1u;
    alarm(5);
}
