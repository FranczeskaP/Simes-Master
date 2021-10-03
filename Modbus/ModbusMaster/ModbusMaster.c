#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "Modbus.h"
#include "ModbusMaster.h"
#include "Decoder.h"
#include "PostData.h"

#define TIME_MS     (2u)

static uint8_t schedulerCalled = 0u;
uint16_t rxData[11];
struct timespec WaitTime = {
    .tv_sec = 0,
    .tv_nsec = TIME_MS * 1000000,
};

static void ModbusSchedulerCalled(int signum);

void ModbusMainFunction(void)
{
    uint8_t dataReceiveError = 0u;
    signal(SIGALRM, ModbusSchedulerCalled);
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
                dataReceiveError = 0u;
                DecodeModbus(DC_FIRST_CHANNEL, "Sensor1", modbusSensors[slave0].receivedData, &DcDecodedData[slave0]);
                DecodeModbus(DC_FIRST_CHANNEL, "Sensor2", modbusSensors[slave1].receivedData, &DcDecodedData[slave1]);
                DecodeModbus(DC_FIRST_CHANNEL, "Sensor3", modbusSensors[slave2].receivedData, &DcDecodedData[slave2]);
                DecodeModbus(DC_FIRST_CHANNEL, "Sensor4", modbusSensors[slave3].receivedData, &DcDecodedData[slave3]);
                DecodeModbus(DC_FIRST_CHANNEL, "Sensor5", modbusSensors[slave4].receivedData, &DcDecodedData[slave4]);
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
            ModbusDeInit();
            DeInitCurl();
            break;
        }
    }
}


static void ModbusSchedulerCalled(int signum)
{
    schedulerCalled = 1u;
    alarm(5);
}

