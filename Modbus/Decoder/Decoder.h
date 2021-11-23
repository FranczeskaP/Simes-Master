#ifndef DECODER_H
#define DECODER_H

#include <stdint.h>
#include "Modbus.h"
#include "Configuration.h"

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
}DcDecodedData_t;

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
}AcDecodedData_t;

typedef struct
{
    DcDecodedData_t dcData[numOfDcSlaves];
    AcDecodedData_t acData;
}DecodedData_t;

extern DecodedData_t DecodedData;

extern void DecodeDc(uint8_t channelUsed, char* sensorName, uint16_t *rxBuffer, DcDecodedData_t * decodedData, CommunicationProtocols_e comProt);
extern void DecodeAc(AcDecodedData_t * decodedData, CommunicationProtocols_e comProt);

#endif
