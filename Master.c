#include "MqttMaster.h"
#include <signal.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include "Configuration.h"
#include "Modbus.h"
#include "PostData.h"

static uint8_t schedulerCalled = 0u;
static void Initiaization(void);
static void SchedulerCalled(int signum);
static void DeInitiaization(void);
static void DecodeAllData(void);

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
                ReadMqtt();
                CheckIfAllUpdated();
                dataReceiveError = 0u;
                DecodeAllData();
                //PerformPost(CreateStringToBePostedModbus(DecodedData));
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
    signal(SIGALRM, SchedulerCalled);
    alarm(5);
    ModbusInit();
    MqttInit();
    InitCurl();
}

static void DeInitiaization(void)
{
    ModbusDeInit();
    DeInitCurl();
}


static void SchedulerCalled(int signum)
{
    schedulerCalled = 1u;
    alarm(5);
}

static void DecodeAllData(void)
{
    for(uint8_t i = 0u; i < MAX_NUM_OF_SENSORS-1; i++)
    {
        if(!configurationData[i].acSensor)
        {
            uint8_t decoderNum = 0u;
            if(configurationData[i].channel1Used && configurationData[i].channel2Used)
            {
                DecodeDc(DC_FIRST_CHANNEL, configurationData[i].channel1Name, modbusDcSensors[configurationData[i].id-1].receivedData, &DecodedData.dcData[decoderNum], configurationData[i].communicationProtocol);
                decoderNum++;
                DecodeDc(DC_SECOND_CHANNEL, configurationData[i].channel2Name, modbusDcSensors[configurationData[i].id-1].receivedData, &DecodedData.dcData[decoderNum], configurationData[i].communicationProtocol);
                decoderNum++;
            }
            else if(configurationData[i].channel1Used)
            {
                DecodeDc(DC_FIRST_CHANNEL, configurationData[i].channel1Name, modbusDcSensors[configurationData[i].id-1].receivedData, &DecodedData.dcData[decoderNum], configurationData[i].communicationProtocol);
                decoderNum++;
            }
            else if(configurationData[i].channel2Used)
            {
                DecodeDc(DC_SECOND_CHANNEL, configurationData[i].channel2Name, modbusDcSensors[configurationData[i].id-1].receivedData, &DecodedData.dcData[decoderNum], configurationData[i].communicationProtocol);
                decoderNum++;
            }
        }                
    }
    for(uint8_t j = 0u; j < MAX_NUM_OF_SENSORS; j++)
    {
        if(configurationData[j].acSensor)
        {
            DecodeAc(&DecodedData.acData, configurationData[j].communicationProtocol);
        }
    }
}
