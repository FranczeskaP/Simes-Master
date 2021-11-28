#ifndef MY_MODBUS_H
#define MY_MODBUS_H

#include <stdint.h>
#include <modbus.h>

#define NUM_OF_AC_REGISTERS  (18u)

typedef struct
{
    uint16_t slaveNum;
    modbus_t *slave;
    uint16_t receivedData[NUM_OF_AC_REGISTERS];
}ModbusDataAc_t;

typedef struct 
{
    ModbusDataAc_t acSensor;
}ModbusData_t;

extern ModbusData_t modbusSensors;

extern void ModbusInit(void);
extern void ModbusDeInit(void);
extern uint8_t ModubsReadData(void);

#endif
