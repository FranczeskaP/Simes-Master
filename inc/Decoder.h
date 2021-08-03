#ifndef DECODER_H
#define DECODER_H

#include <stdint.h>

typedef struct
{
    double temperature;
    double voltage1;
    double current1;
    double voltage2;
    double current2;
    double power1;
    double power2;
    uint16_t efficiency;
    double electricCharge1;
    double electricCharge2;
    double energy1;
    double energy2;
}DecodedData_t;

extern void DecodeModbus(uint16_t *rxBuffer, DecodedData_t * decodedData);

#endif
