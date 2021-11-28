#ifndef MY_MODBUS_H
#define MY_MODBUS_H

#include <stdint.h>
#include <modbus.h>

#define NUM_OF_DC_REGISTERS  (18u)
#define NUM_OF_AC_REGISTERS  (18u)

typedef enum
{
    slave0 = 0u,
    slave1 = 1u,
    slave2 = 2u,
    slave3 = 3u,
    slave4 = 4u,
    numOfDcSlaves
}DcSlaves;

typedef struct
{
    uint16_t slaveNum;
    modbus_t *slave;
    uint16_t receivedData[NUM_OF_DC_REGISTERS];
}ModbusDataDc_t;

typedef struct
{
    uint16_t slaveNum;
    modbus_t *slave;
    uint16_t receivedData[NUM_OF_AC_REGISTERS];
}ModbusDataAc_t;

typedef struct 
{
    ModbusDataDc_t dcSensors[numOfDcSlaves];
    ModbusDataAc_t acSensor;
}ModbusData_t;

extern ModbusData_t modbusSensors;
extern ModbusDataDc_t modbusDcSensors[numOfDcSlaves];

extern void ModbusInit(void);
extern void ModbusDeInit(void);
extern uint8_t ModubsReadData(void);

#endif
