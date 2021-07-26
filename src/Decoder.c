#include <stdint.h>
#include "Decoder.h"

#define TEMPERATURE_MASK    (0x3FFFu)
#define POWER_MASK          (0x3FFFu)
#define CURRENT_MASK        (0x3FFFu)
#define SIGN_MASK           (0x8000u)
#define UNIT_MASK           (0x4000u)
#define INTEGER_MASK        (0x3FFu)
#define DECIMAL_MASK        (0x7Fu)

static double DecodeTemperature(uint16_t tempBuffer);
static double DecodeVoltage(uint16_t integerBuffer, uint16_t decimalBuffer);
static double DecodeCurrent(uint16_t currentBuffer);
static double DecodePower(uint16_t powerBuffer);

void DecodeModbus(uint16_t *rxBuffer, DecodedData_t * decodedData)
{
    decodedData->temperature = DecodeTemperature(rxBuffer[0]);
    decodedData->voltage1 = DecodeVoltage(rxBuffer[1], rxBuffer[2]);
    decodedData->current1 = DecodeCurrent(rxBuffer[3]);
    decodedData->voltage2 = DecodeVoltage(rxBuffer[4], rxBuffer[5]);
    decodedData->current2 = DecodeCurrent(rxBuffer[6]);
    decodedData->power1 = DecodePower(rxBuffer[7]);
    decodedData->power2 = DecodePower(rxBuffer[8]);
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

