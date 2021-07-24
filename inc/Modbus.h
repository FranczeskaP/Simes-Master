#ifndef MODBUS_H
#define MODBUS_H

#include <stdint.h>
#define NUM_OF_SLAVE_REGISTERS  (11u)

void ModbusInit(void);
void ModbusDeInit(void);
void ModbusReadData(uint16_t slaveNum, uint16_t receivedData[NUM_OF_SLAVE_REGISTERS]);

#endif
