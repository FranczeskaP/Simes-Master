#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "Decoder.h"
#include "DataTypes.h"

#define TEMPERATURE_MASK        (0xFFu)
#define CURRENT_MASK            (0x1FFu)
#define VOLTAGE_MASK            (0x3FFu)
#define SIGN_MASK               (0x8000u)
#define INTEGER_MASK            (0xFFu)
#define NUM_OF_CYCLES_MASK      (0x3FFu)
#define STATUS_MASK             (0x01u)
#define INSOLATION_MASK         (0x3FFu)
#define CHARGE_MASK             (0x7Fu)
#define CAPACITY_MASK           (0x7Fu)
#define DC_FIRST_CHANNEL           (1u)
#define DC_SECOND_CHANNEL          (2u)
#define ERROR_DOUBLE            (255.f)
#define ERROR_UINT              (255u)

typedef union {

	float f;
	struct
	{
		uint32_t mantissa : 23;
		uint32_t exponent : 8;
		uint32_t sign : 1;

	} raw;
} decodedAc_t;

static void DecodeDcModbus(uint16_t *rxBuffer, DcDecodedData_t * decodedData);
static void DecodeDcMqtt(char *rxBuffer[TotalNumOfDcSensorTopics], DcDecodedData_t * decodedData, uint8_t channelUsed, MqttStruct_t mqttData[TotalNumOfDcSensorTopics]);
static void DecodeDcNotUpdated(DcDecodedData_t * decodedData);
static void DecodeAcModbus(AcDecodedData_t * decodedData);
static void DecodeAcMqtt(AcDecodedData_t * decodedData);
static void DecodeAcNotUpdated(AcDecodedData_t * decodedData);
static double DecodeTemperature(uint16_t tempBuffer);
static double DecodeVoltage(uint16_t voltageBuffer);
static double DecodeCurrent(uint16_t currentBuffer);
static double DecodePower(uint16_t powerInteger, uint16_t powerDecimal);
static double DecodeEnergy(uint16_t energyInteger, uint16_t energyDecimal);
static uint16_t DecodeStatus(uint16_t status);
static double DecodeQ(uint16_t qInteger, uint16_t qDecimal);
static double DecodeNumOfCycles(uint16_t numOfCycles);
static double DecodeChargeDegree(uint16_t chargeDegree);
static double DecodeCapacity(uint16_t capacity);
static double DecodeInsolation(uint16_t insolation);
static uint32_t ConvertToInt(uint32_t data, uint32_t low, uint32_t high);
static float DecodeAc(uint16_t high, uint16_t low);

void DecodeData(void)
{
    if(AcSensorData.communicationProtocol == Modbus)
    {
        if(AcSensorData.updated)
        {
            DecodeAcModbus(&AcSensorData.acDecodedData);
        }
        else
        {
            DecodeAcNotUpdated(&AcSensorData.acDecodedData);
        }
    }
    else if(AcSensorData.communicationProtocol == Mqtt)
    {
        DecodeAcMqtt(&AcSensorData.acDecodedData);
    }
    
    for(uint8_t i = 0u; i < numOfDcSlaves; i++)
    {
        if(DcSensorData[i].communicationProtocol == Modbus)
        {
            if(DcSensorData[i].updated)
            {
                DecodeDcModbus(DcSensorData[i].modbusReceivedData, &DcSensorData[i].dcDecodedData);
            }
            else
            {
                DecodeDcNotUpdated(&DcSensorData[i].dcDecodedData);
            }
        }
        else if(DcSensorData[i].communicationProtocol == Mqtt)
        {
            /*
            DecodeDcMqtt(DcSensorData[i].mqttReceivedData, &DcSensorData[i].dcDecodedDataCh1, DC_FIRST_CHANNEL, DcSensorData[i].dcSensorMqttData);
            DecodeDcMqtt(DcSensorData[i].mqttReceivedData, &DcSensorData[i].dcDecodedDataCh1, DC_SECOND_CHANNEL, DcSensorData[i].dcSensorMqttData);
            */
        }
    }
}

static void DecodeDcModbus(uint16_t *rxBuffer, DcDecodedData_t * decodedData)
{
    decodedData->voltageCh1 = DecodeVoltage(rxBuffer[0]);
    decodedData->currentCh1 = DecodeCurrent(rxBuffer[1]);
    decodedData->pPowerCh1 = DecodePower(rxBuffer[2], rxBuffer[3]);
    decodedData->energyCh1 = DecodeEnergy(rxBuffer[4], rxBuffer[5]);
    decodedData->statusCh1 = DecodeStatus(rxBuffer[6]);
    decodedData->temperatureCh1 = DecodeTemperature(rxBuffer[7]);
    decodedData->qPowerCh1 = DecodeQ(rxBuffer[8], rxBuffer[9]);
    decodedData->numOfCycles = DecodeNumOfCycles(rxBuffer[10]);
    decodedData->voltageCh2 = DecodeVoltage(rxBuffer[11]);
    decodedData->currentCh2 = DecodeCurrent(rxBuffer[12]);
    decodedData->pPowerCh2 = DecodePower(rxBuffer[13], rxBuffer[14]);
    decodedData->energyCh2 = DecodeEnergy(rxBuffer[15], rxBuffer[16]);
    decodedData->statusCh2 = DecodeStatus(rxBuffer[17]);
    decodedData->temperatureCh2 = DecodeTemperature(rxBuffer[18]);
    decodedData->chargeDegree = DecodeChargeDegree(rxBuffer[19]);
    decodedData->capacity = DecodeCapacity(rxBuffer[20]);
    decodedData->insolation = DecodeInsolation(rxBuffer[21]);
    decodedData->energy = DecodeEnergy(rxBuffer[22], rxBuffer[23]);
}

static void DecodeDcMqtt(char *rxBuffer[TotalNumOfDcSensorTopics], DcDecodedData_t * decodedData, uint8_t channelUsed, MqttStruct_t mqttData[TotalNumOfDcSensorTopics])
{
/*
    decodedData->temperature = mqttData[Temp].topicUpdated ? atof(rxBuffer[Temp]) : ERROR_DOUBLE;
    decodedData->efficiency = mqttData[Eff].topicUpdated ? (uint16_t)atoi(rxBuffer[Eff]) : ERROR_UINT;
    if(DC_FIRST_CHANNEL == channelUsed)
    {
        decodedData->voltage = mqttData[Ch2].topicUpdated ? atof(rxBuffer[Ch2]) : ERROR_DOUBLE;
        decodedData->current = mqttData[Ch1].topicUpdated ? atof(rxBuffer[Ch1]) : ERROR_DOUBLE;
        decodedData->power = mqttData[P1].topicUpdated ? atof(rxBuffer[P1]) : ERROR_DOUBLE;
        decodedData->electricCharge = mqttData[QCh1].topicUpdated ? atof(rxBuffer[QCh1]) : ERROR_DOUBLE;
        decodedData->energy = mqttData[EnergyCh1].topicUpdated ? atof(rxBuffer[EnergyCh1]) : ERROR_DOUBLE;
    }
    else if(DC_SECOND_CHANNEL == channelUsed)
    {
        decodedData->voltage = mqttData[Ch4].topicUpdated ? atof(rxBuffer[Ch4]) : ERROR_DOUBLE;
        decodedData->current = mqttData[Ch3].topicUpdated ? atof(rxBuffer[Ch3]) : ERROR_DOUBLE;
        decodedData->power = mqttData[P2].topicUpdated ? atof(rxBuffer[P2]) : ERROR_DOUBLE;
        decodedData->electricCharge = mqttData[QCh2].topicUpdated ? atof(rxBuffer[QCh2]) : ERROR_DOUBLE;
        decodedData->energy = mqttData[EnergyCh2].topicUpdated ? atof(rxBuffer[EnergyCh2]) : ERROR_DOUBLE;
    }
    */
}

static void DecodeDcNotUpdated(DcDecodedData_t * decodedData)
{
    decodedData->voltageCh1 = ERROR_DOUBLE;
    decodedData->currentCh1 = ERROR_DOUBLE;
    decodedData->pPowerCh1 = ERROR_DOUBLE;
    decodedData->energyCh1 = ERROR_DOUBLE;
    decodedData->statusCh1 = ERROR_DOUBLE;
    decodedData->temperatureCh1 = ERROR_DOUBLE;
    decodedData->qPowerCh1 = ERROR_DOUBLE;
    decodedData->numOfCycles = ERROR_DOUBLE;
    decodedData->voltageCh2 = ERROR_DOUBLE;
    decodedData->currentCh2 = ERROR_DOUBLE;
    decodedData->pPowerCh2 = ERROR_DOUBLE;
    decodedData->energyCh2 = ERROR_DOUBLE;
    decodedData->statusCh2 = ERROR_DOUBLE;
    decodedData->temperatureCh2 = ERROR_DOUBLE;
    decodedData->chargeDegree = ERROR_DOUBLE;
    decodedData->capacity = ERROR_DOUBLE;
    decodedData->insolation = ERROR_DOUBLE;
    decodedData->energy = ERROR_DOUBLE;
}

static void DecodeAcModbus(AcDecodedData_t * decodedData)
{
    decodedData->voltage1Rms = DecodeAc(AcSensorData.modbbusData1.buffer[0], AcSensorData.modbbusData1.buffer[1]);
    decodedData->voltage2Rms = DecodeAc(AcSensorData.modbbusData1.buffer[2], AcSensorData.modbbusData1.buffer[3]);
    decodedData->voltage3Rms = DecodeAc(AcSensorData.modbbusData1.buffer[4], AcSensorData.modbbusData1.buffer[5]);
    decodedData->current1Rms = DecodeAc(AcSensorData.modbbusData1.buffer[6], AcSensorData.modbbusData1.buffer[7]);
    decodedData->current2Rms = DecodeAc(AcSensorData.modbbusData1.buffer[8], AcSensorData.modbbusData1.buffer[9]);
    decodedData->current3Rms = DecodeAc(AcSensorData.modbbusData1.buffer[10], AcSensorData.modbbusData1.buffer[11]);
    decodedData->pPower = DecodeAc(AcSensorData.modbbusData2.buffer[0], AcSensorData.modbbusData2.buffer[1]);
    decodedData->qPower = DecodeAc(AcSensorData.modbbusData2.buffer[4], AcSensorData.modbbusData2.buffer[5]);
    decodedData->sPower = DecodeAc(AcSensorData.modbbusData2.buffer[2], AcSensorData.modbbusData2.buffer[3]);
    decodedData->pEnergy = DecodeAc(AcSensorData.modbbusData2.buffer[12], AcSensorData.modbbusData2.buffer[13]);
    decodedData->qEnergy = DecodeAc(AcSensorData.modbbusData4.buffer[0], AcSensorData.modbbusData4.buffer[1]);
    decodedData->currentThd = DecodeAc(AcSensorData.modbbusData3.buffer[2], AcSensorData.modbbusData3.buffer[3]);
    decodedData->voltageThd = DecodeAc(AcSensorData.modbbusData3.buffer[0], AcSensorData.modbbusData3.buffer[1]);
    decodedData->powerCos = DecodeAc(AcSensorData.modbbusData2.buffer[6], AcSensorData.modbbusData2.buffer[7]);
    decodedData->frequence = DecodeAc(AcSensorData.modbbusData2.buffer[10], AcSensorData.modbbusData2.buffer[11]);
    decodedData->status = 0u;
}

static void DecodeAcMqtt(AcDecodedData_t * decodedData)
{
    decodedData->voltage1Rms = 0.f;
    decodedData->voltage2Rms = 0.f;
    decodedData->voltage3Rms = 0.f;
    decodedData->current1Rms = 0.f;
    decodedData->current2Rms = 0.f;
    decodedData->current3Rms = 0.f;
    decodedData->pPower = 0.f;
    decodedData->qPower = 0.f;
    decodedData->sPower = 0.f;
    decodedData->pEnergy = 0.f;
    decodedData->qEnergy = 0.f;
    decodedData->currentThd = 0.f;
    decodedData->voltageThd = 0.f;
    decodedData->powerCos = 0.f;
    decodedData->frequence = 0.f;
    decodedData->status = 0u;
}

static void DecodeAcNotUpdated(AcDecodedData_t * decodedData)
{
    decodedData->voltage1Rms = ERROR_DOUBLE;
    decodedData->voltage2Rms = ERROR_DOUBLE;
    decodedData->voltage3Rms = ERROR_DOUBLE;
    decodedData->current1Rms = ERROR_DOUBLE;
    decodedData->current2Rms = ERROR_DOUBLE;
    decodedData->current3Rms = ERROR_DOUBLE;
    decodedData->pPower = ERROR_DOUBLE;
    decodedData->qPower = ERROR_DOUBLE;
    decodedData->sPower = ERROR_DOUBLE;
    decodedData->pEnergy = ERROR_DOUBLE;
    decodedData->qEnergy = ERROR_DOUBLE;
    decodedData->currentThd = ERROR_DOUBLE;
    decodedData->voltageThd = ERROR_DOUBLE;
    decodedData->powerCos = ERROR_DOUBLE;
    decodedData->frequence = ERROR_DOUBLE;
    decodedData->status = ERROR_UINT;
}

static double DecodeTemperature(uint16_t tempBuffer)
{
    double temperature = 0;
    temperature = (double)(tempBuffer & TEMPERATURE_MASK);

    if((tempBuffer & SIGN_MASK) > 0u)
    {
        temperature = -temperature;
    } 
    return temperature;
}

static double DecodeVoltage(uint16_t voltageBuffer)
{
    return (voltageBuffer & VOLTAGE_MASK);
}

static double DecodeCurrent(uint16_t currentBuffer)
{
    double current = 0;
    current = (double)(currentBuffer & CURRENT_MASK);
    if((currentBuffer & SIGN_MASK) > 0u)
    {
        current = -current;
    } 
    return current;
}

static double DecodePower(uint16_t powerInteger, uint16_t powerDecimal)
{
    double power = 0;
    power = (double)((powerInteger & INTEGER_MASK) << 16);
    power += powerDecimal;
    power /= 10;

    if((powerInteger & SIGN_MASK) > 0u)
    {
        power = -power;
    } 
    return power;
}

static double DecodeEnergy(uint16_t energyInteger, uint16_t energyDecimal)
{
    double energy = 0;
    energy = (double)((energyInteger & INTEGER_MASK) << 16);
    energy += energyDecimal;
    energy /= 10;

    if((energyInteger & SIGN_MASK) > 0u)
    {
        energy = -energy;
    } 
    return energy;
}

static uint16_t DecodeStatus(uint16_t status)
{
    return (status & STATUS_MASK);
}


static double DecodeQ(uint16_t qInteger, uint16_t qDecimal)
{
    double q = 0;
    q = (double)((qInteger & INTEGER_MASK) << 16);
    q += qDecimal;
    q /= 10;

    if((qInteger & SIGN_MASK) > 0u)
    {
        q = -q;
    } 
    return q;
}

static double DecodeNumOfCycles(uint16_t numOfCycles)
{
    return (numOfCycles & NUM_OF_CYCLES_MASK);
}

static double DecodeChargeDegree(uint16_t chargeDegree)
{
    return (chargeDegree & CHARGE_MASK);
}

static double DecodeCapacity(uint16_t capacity)
{
    return (capacity & CAPACITY_MASK);
}

static double DecodeInsolation(uint16_t insolation)
{
    return (insolation & INSOLATION_MASK);
}

static uint32_t ConvertToInt(uint32_t data, uint32_t low, uint32_t high)
{
	uint32_t f = 0, i;
	for (i = high; i >= low; i--) {
		f = f + ((data >> i) & 0x1) * pow(2, high - i);
	}
	return f;
}

static float DecodeAc(uint16_t high, uint16_t low)
{
    decodedAc_t var;
    uint32_t x = (high << 16) | low;
	uint32_t f = ConvertToInt(x, 9, 31);
	var.raw.mantissa = f;
	f = ConvertToInt(x, 1, 8);
	var.raw.exponent = f;
	var.raw.sign = ((x >> 31) & 0x01u);
    return var.f;
}

