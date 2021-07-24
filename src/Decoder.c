#include <stdint.h>
#include "Decoder.h"

#define TEMPERATURE_MASK    (0x3FFFu)
#define POWER_MASK          (0x3FFFu)
#define CURRENT_MASK        (0x3FFFu)
#define SIGN_MASK           (0x8000u)
#define UNIT_MASK           (0x4000u)
#define INTEGER_MASK        (0x3FFu)
#define DECIMAL_MASK        (0x7Fu)

static float DecodeTemperature(uint16_t tempBuffer);
static float DecodeVoltage(uint16_t integerBuffer, uint16_t decimalBuffer);
static float DecodeCurrent(uint16_t currentBuffer);
static float DecodePower(uint16_t powerBuffer);

void DecodeModbus(uint16_t rxBuffer[9], DecodedData_t * decodedData)
{
    decodedData->temperature = DecodeTemperature(rxBuffer[0]);
    decodedData->voltage1 = DecodeVoltage(rxBuffer[1], rxBuffer[2]);
    decodedData->current1 = DecodeCurrent(rxBuffer[3]);
    decodedData->voltage2 = DecodeVoltage(rxBuffer[4], rxBuffer[5]);
    decodedData->current2 = DecodeCurrent(rxBuffer[6]);
    decodedData->power1 = DecodePower(rxBuffer[7]);
    decodedData->power2 = DecodePower(rxBuffer[8]);
}

static float DecodeTemperature(uint16_t tempBuffer)
{
    float temperature = 0.f;
    temperature = (float)(tempBuffer & TEMPERATURE_MASK);
    temperature /= 10;

    if((tempBuffer & SIGN_MASK) == 1u)
    {
        temperature = -temperature;
    } 
    return temperature;
}

static float DecodeVoltage(uint16_t integerBuffer, uint16_t decimalBuffer)
{
    float voltage = 0.f;
    uint16_t integer = 0u;
    float decimal = 0.f;
    voltage = (float)(integerBuffer & INTEGER_MASK);
    decimal = (float)(decimalBuffer & DECIMAL_MASK);
    decimal /= 100;
    voltage += decimal;
    
    if((integerBuffer & UNIT_MASK) == 1u)
    {
        voltage /= 1000;
    }
    if((integerBuffer & SIGN_MASK) == 1u)
    {
        voltage = -voltage;
    }
    return voltage;
}

static float DecodeCurrent(uint16_t currentBuffer)
{
    float current = 0.f;
    current = (float)(currentBuffer & CURRENT_MASK);
    current /= 100;

    if((currentBuffer & UNIT_MASK) == 1u)
    {
        current /= 1000;
    }  
    if((currentBuffer & SIGN_MASK) == 1u)
    {
        current = -current;
    } 
    return current;
}

static float DecodePower(uint16_t powerBuffer)
{
    float power = 0.f;
    power = (float)(powerBuffer & POWER_MASK);
    power /= 10;

    if((powerBuffer & SIGN_MASK) == 1u)
    {
        power = -power;
    } 
    return power;
}

