#ifndef MY_MODBUS_H
#define MY_MODBUS_H

#include <stdint.h>
#include <modbus.h>

#define NUM_OF_SLAVE_REGISTERS  (18u)

typedef enum
{
    slave0 = 0u,
    slave1 = 1u,
    slave2 = 2u,
    slave3 = 3u,
    slave4 = 4u,
    numOfSlaves
}Slaves;

typedef struct
{
    uint16_t slaveNum;
    modbus_t *slave;
    uint16_t receivedData[NUM_OF_SLAVE_REGISTERS];
}ModbusData_t;

extern ModbusData_t modbusSensors[numOfSlaves];

extern void ModbusInit(void);
extern void ModbusDeInit(void);
extern uint8_t ModbusReadData(uint16_t slaveNum);

#endif
