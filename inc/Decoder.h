#ifndef DECODER_H
#define DECODER_H

#include <stdint.h>

typedef struct
{
    float temperature;
    float voltage1;
    float current1;
    float voltage2;
    float current2;
    float power1;
    float power2;
}DecodedData_t;


void DecodeModbus(uint16_t rxBuffer[9], DecodedData_t * decodedData);

#endif