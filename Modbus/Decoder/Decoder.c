#include <stdint.h>
#include "Decoder.h"

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
DecodedData_t DecodedData;
DecodedData_t DcDecodedData[numOfDcSlaves];

static void DecodeDcModbus(uint8_t channelUsed, char* sensorName, uint16_t *rxBuffer, DcDecodedData_t * decodedData);
static void DecodeAcModbus(AcDecodedData_t * decodedData);
static void DecodeAcMqtt(AcDecodedData_t * decodedData);
static void DecodeDcMqtt(DcDecodedData_t * decodedData);
static double DecodeTemperature(uint16_t tempBuffer);
static double DecodeVoltage(uint16_t integerBuffer, uint16_t decimalBuffer);
static double DecodeCurrent(uint16_t currentBuffer);
static double DecodePower(uint16_t powerBuffer);
static uint16_t DecodeEfficiency(uint16_t efficiencyBuffer);
static double DecodeElectricCharge(uint16_t integerBuffer, uint16_t decimalBuffer);
static double DecodeEnergy(uint16_t integerBuffer, uint16_t decimalBuffer);

void DecodeDc(uint8_t channelUsed, char* sensorName, uint16_t *rxBuffer, DcDecodedData_t * decodedData, CommunicationProtocols_e comProt)
{
    if(comProt == Modbus)
    {
        DecodeDcModbus(channelUsed, sensorName, rxBuffer, decodedData);
    }
    else if(comProt == Mqtt)
    {
        DecodeDcMqtt(decodedData);
    }
}

void DecodeAc(AcDecodedData_t * decodedData, CommunicationProtocols_e comProt)
{
    if(comProt == Modbus)
    {
        DecodeAcModbus(decodedData);
    }
    else if(comProt == Mqtt)
    {
        DecodeAcMqtt(decodedData);
    }
}

void DecodeDcModbus(uint8_t channelUsed, char* sensorName, uint16_t *rxBuffer, DcDecodedData_t * decodedData)
{
    decodedData->name = sensorName;
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

void DecodeAcModbus(AcDecodedData_t * decodedData)
{
    /* todo */
}

void DecodeAcMqtt(AcDecodedData_t * decodedData)
{
    /* todo */
}

void DecodeDcMqtt(DcDecodedData_t * decodedData)
{
    /* todo */
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
