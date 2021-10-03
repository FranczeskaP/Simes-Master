#ifndef DECODER_H
#define DECODER_H

#include <stdint.h>
#include "Modbus.h"

#define DC_FIRST_CHANNEL           (1u)
#define DC_SECOND_CHANNEL          (2u)

typedef struct
{
    char *name;
    double temperature;
    double voltage;
    double current;
    double power;
    uint16_t efficiency;
    double electricCharge;
    double energy;
}DecodedData_t;

extern DecodedData_t decodedData[numOfSlaves];

extern void DecodeModbus(uint8_t channelUsed, char* sensorName, uint16_t *rxBuffer, DecodedData_t * decodedData);

#endif
