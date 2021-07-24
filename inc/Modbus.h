#ifndef MODBUS_H
#define MODBUS_H

#include <stdint.h>

void ModbusInit(void);
void ModbusDeInit(void);
void ModbusReadData(uint16_t slaveNum);

#endif
