#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "Decoder.h"
#include "DataTypes.h"

#define TEMPERATURE_MASK        (0x3FFFu)
#define POWER_MASK              (0x3FFFu)
#define CURRENT_MASK            (0x3FFFu)
#define SIGN_MASK               (0x8000u)
#define UNIT_MASK               (0x4000u)
#define INTEGER_MASK            (0x3FFu)
#define DECIMAL_MASK            (0x7Fu)
#define PERCENTAGE_MASK         (0x7Fu)
#define E_Q_INTEGER_MASK        (0xFFF0u)
#define E_Q_DECIMAL_HIGH_MASK   (0x0Fu)
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

static void DecodeDcModbus(uint16_t *rxBuffer, DcDecodedData_t * decodedData, uint8_t channelUsed);
static void DecodeDcMqtt(char *rxBuffer[TotalNumOfDcSensorTopics], DcDecodedData_t * decodedData, uint8_t channelUsed, MqttStruct_t mqttData[TotalNumOfDcSensorTopics]);
static void DecodeDcNotUpdated(DcDecodedData_t * decodedData, uint8_t channelUsed);
static void DecodeAcModbus(AcDecodedData_t * decodedData);
static void DecodeAcMqtt(AcDecodedData_t * decodedData);
static void DecodeAcNotUpdated(AcDecodedData_t * decodedData);
static double DecodeTemperature(uint16_t tempBuffer);
static double DecodeVoltage(uint16_t integerBuffer, uint16_t decimalBuffer);
static double DecodeCurrent(uint16_t currentBuffer);
static double DecodePower(uint16_t powerBuffer);
static uint16_t DecodeEfficiency(uint16_t efficiencyBuffer);
static double DecodeElectricCharge(uint16_t integerBuffer, uint16_t decimalBuffer);
static double DecodeEnergy(uint16_t integerBuffer, uint16_t decimalBuffer);
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
                DecodeDcModbus(DcSensorData[i].modbusReceivedData, &DcSensorData[i].dcDecodedDataCh1, DC_FIRST_CHANNEL);
                DecodeDcModbus(DcSensorData[i].modbusReceivedData, &DcSensorData[i].dcDecodedDataCh2, DC_SECOND_CHANNEL);
            }
            else
            {
                DecodeDcNotUpdated(&DcSensorData[i].dcDecodedDataCh1, DC_FIRST_CHANNEL);
                DecodeDcNotUpdated(&DcSensorData[i].dcDecodedDataCh2, DC_SECOND_CHANNEL);
            }
        }
        else if(DcSensorData[i].communicationProtocol == Mqtt)
        {
            DecodeDcMqtt(DcSensorData[i].mqttReceivedData, &DcSensorData[i].dcDecodedDataCh1, DC_FIRST_CHANNEL, DcSensorData[i].dcSensorMqttData);
            DecodeDcMqtt(DcSensorData[i].mqttReceivedData, &DcSensorData[i].dcDecodedDataCh1, DC_SECOND_CHANNEL, DcSensorData[i].dcSensorMqttData);
        }
    }
}

static void DecodeDcModbus(uint16_t *rxBuffer, DcDecodedData_t * decodedData, uint8_t channelUsed)
{
    decodedData->temperature = DecodeTemperature(rxBuffer[0]);
    decodedData->efficiency = DecodeEfficiency(rxBuffer[9]);
    if(DC_FIRST_CHANNEL == channelUsed)
    {
        decodedData->voltage = DecodeVoltage(rxBuffer[1], rxBuffer[2]);
        decodedData->current = DecodeCurrent(rxBuffer[3]);
        decodedData->power = DecodePower(rxBuffer[7]);
        decodedData->electricCharge = DecodeElectricCharge(rxBuffer[10], rxBuffer[11]);
        decodedData->energy = DecodeEnergy(rxBuffer[14], rxBuffer[15]);
    }
    else if(DC_SECOND_CHANNEL == channelUsed)
    {
        decodedData->voltage = DecodeVoltage(rxBuffer[4], rxBuffer[5]);
        decodedData->current = DecodeCurrent(rxBuffer[6]);
        decodedData->power = DecodePower(rxBuffer[8]);
        decodedData->electricCharge = DecodeElectricCharge(rxBuffer[12], rxBuffer[13]);
        decodedData->energy = DecodeEnergy(rxBuffer[16], rxBuffer[17]);
    }
}

static void DecodeDcMqtt(char *rxBuffer[TotalNumOfDcSensorTopics], DcDecodedData_t * decodedData, uint8_t channelUsed, MqttStruct_t mqttData[TotalNumOfDcSensorTopics])
{

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
}

static void DecodeDcNotUpdated(DcDecodedData_t * decodedData, uint8_t channelUsed)
{
    decodedData->temperature = ERROR_DOUBLE;
    decodedData->efficiency = ERROR_UINT;
    if(DC_FIRST_CHANNEL == channelUsed)
    {
        decodedData->voltage = ERROR_DOUBLE;
        decodedData->current = ERROR_DOUBLE;
        decodedData->power = ERROR_DOUBLE;
        decodedData->electricCharge = ERROR_DOUBLE;
        decodedData->energy = ERROR_DOUBLE;
    }
    else if(DC_SECOND_CHANNEL == channelUsed)
    {
        decodedData->voltage = ERROR_DOUBLE;
        decodedData->current = ERROR_DOUBLE;
        decodedData->power = ERROR_DOUBLE;
        decodedData->electricCharge = ERROR_DOUBLE;
        decodedData->energy = ERROR_DOUBLE;
    }
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
    temperature /= 10;

    if((tempBuffer & SIGN_MASK) > 0u)
    {
        temperature = -temperature;
    } 
    return temperature;
}

static double DecodeVoltage(uint16_t integerBuffer, uint16_t decimalBuffer)
{
    double voltage = 0;
    uint16_t integer = 0u;
    double decimal = 0;
    voltage = (double)(integerBuffer & INTEGER_MASK);
    decimal = (double)(decimalBuffer & DECIMAL_MASK);
    decimal /= 100;
    voltage += decimal;
    
    if((integerBuffer & UNIT_MASK) > 0u)
    {
        voltage /= 1000;
    }
    if((integerBuffer & SIGN_MASK) > 0u)
    {
        voltage = -voltage;
    }
    return voltage;
}

static double DecodeCurrent(uint16_t currentBuffer)
{
    double current = 0;
    current = (double)(currentBuffer & CURRENT_MASK);
    current /= 100;

    if((currentBuffer & UNIT_MASK) > 0u)
    {
        current /= 1000;
    }  
    if((currentBuffer & SIGN_MASK) > 0u)
    {
        current = -current;
    } 
    return current;
}

static double DecodePower(uint16_t powerBuffer)
{
    double power = 0;
    power = (double)(powerBuffer & POWER_MASK);
    power /= 10;

    if((powerBuffer & SIGN_MASK) > 0u)
    {
        power = -power;
    } 
    return power;
}

static uint16_t DecodeEfficiency(uint16_t efficiencyBuffer)
{
    return (efficiencyBuffer & PERCENTAGE_MASK);
}

static double DecodeElectricCharge(uint16_t integerBuffer, uint16_t decimalBuffer)
{
    double electricCharge = 0;
    uint32_t electricChargeDecimal_u = ((integerBuffer & E_Q_DECIMAL_HIGH_MASK) << 16);
    electricChargeDecimal_u |= decimalBuffer;
    double electricChargeDecimal_d = (double)(electricChargeDecimal_u / 1000000);
    electricCharge = (double)((integerBuffer & E_Q_INTEGER_MASK) >> 4);
    electricCharge += electricChargeDecimal_d;
    return electricCharge;
}

static double DecodeEnergy(uint16_t integerBuffer, uint16_t decimalBuffer)
{
    double energy = 0;
    uint32_t energyDecimal_u = ((integerBuffer & E_Q_DECIMAL_HIGH_MASK) << 16);
    energyDecimal_u |= decimalBuffer;
    double energyDecimal_d = (double)(energyDecimal_u / 1000000);
    energy = (double)((integerBuffer & E_Q_INTEGER_MASK) >> 4);
    energy += energyDecimal_d;
    return energy;
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

