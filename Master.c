//#include "MqttMaster.h"
#include <signal.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include "Configuration.h"
#include "Modbus.h"
#include "PostData.h"

static uint8_t schedulerCalled = 0u;
static void Initiaization(void);
static void ModbusSchedulerCalled(int signum);
static void DeInitiaization(void);

int main()
{
    uint8_t dataReceiveError = 0u;
    Initiaization();
    while(1)
    {
        if(1u == schedulerCalled)
        {
            schedulerCalled = 0u;
            if(0u == ModubsReadData())
            {
                dataReceiveError = 0u;
                DecodeModbus(DC_FIRST_CHANNEL, "Sensor1", modbusDcSensors[slave0].receivedData, &DcDecodedData[slave0]);
                DecodeModbus(DC_FIRST_CHANNEL, "Sensor2", modbusDcSensors[slave1].receivedData, &DcDecodedData[slave1]);
                DecodeModbus(DC_FIRST_CHANNEL, "Sensor3", modbusDcSensors[slave2].receivedData, &DcDecodedData[slave2]);
                DecodeModbus(DC_FIRST_CHANNEL, "Sensor4", modbusDcSensors[slave3].receivedData, &DcDecodedData[slave3]);
                PerformPost(CreateStringToBePostedModbus(DcDecodedData));
                // printf("%f\n", DcDecodedData[0].current1);
                // printf("%f\n", DcDecodedData[0].current2);
                // printf("%u\n", DcDecodedData[0].efficiency);
                // printf("%f\n", DcDecodedData[0].electricCharge1);
                // printf("%f\n", DcDecodedData[0].electricCharge2);
                // printf("%f\n", DcDecodedData[0].energy1);
                // printf("%f\n", DcDecodedData[0].energy2);
                // printf("%f\n", DcDecodedData[0].power1);
                // printf("%f\n", DcDecodedData[0].power2);
                // printf("%f\n", DcDecodedData[0].temperature);
                // printf("%f\n", DcDecodedData[0].voltage1);
                // printf("%f\n", DcDecodedData[0].voltage2);
                // printf("\n");
                // printf("\n");
                // printf("%f\n", DcDecodedData[1].current1);
                // printf("%f\n", DcDecodedData[1].current2);
                // printf("%u\n", DcDecodedData[1].efficiency);
                // printf("%f\n", DcDecodedData[1].electricCharge1);
                // printf("%f\n", DcDecodedData[1].electricCharge2);
                // printf("%f\n", DcDecodedData[1].energy1);
                // printf("%f\n", DcDecodedData[1].energy2);
                // printf("%f\n", DcDecodedData[1].power1);
                // printf("%f\n", DcDecodedData[1].power2);
                // printf("%f\n", DcDecodedData[1].temperature);
                // printf("%f\n", DcDecodedData[1].voltage1);
                // printf("%f\n", DcDecodedData[1].voltage2);
            }
            else
            {
                dataReceiveError++;
            }
        }
        else
        {
            printf(".\n");
        }
        sleep(1);
        if(5u == dataReceiveError)
        {
            break;
        }
    }
    return 0;
}

static void Initiaization(void)
{
    InitConfigData();
    GetConfigurationData();
    ProcessConfigData();
    //signal(SIGALRM, ModbusSchedulerCalled);
    //alarm(5);
    //ModbusInit();
    //InitCurl();
}

static void DeInitiaization(void)
{
    ModbusDeInit();
    DeInitCurl();
}


static void ModbusSchedulerCalled(int signum)
{
    schedulerCalled = 1u;
    alarm(5);
}
