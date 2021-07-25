#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "Modbus.h"

#define DEVICE_NAME             ("/dev/ttyUSB0")
#define BAUDRATE                (115200u)
#define PARITY                  ('N')
#define DATA_BITS               (8u)
#define STOP_BITS               (1u)

ModbusData_t modbusSensors[numOfSlaves];

void ModbusInit(void)
{
    for(uint16_t i = 0u; i < numOfSlaves; i++)
    {
        modbusSensors[i].slave = modbus_new_rtu(DEVICE_NAME, BAUDRATE, PARITY, DATA_BITS, STOP_BITS);
        if (!modbusSensors[i].slave) 
        {
            fprintf(stderr, "Failed to create the context: %s\n", modbus_strerror(errno));
            exit(1);
        }

        if (modbus_connect(modbusSensors[i].slave) == -1) 
        {
            fprintf(stderr, "Unable to connect: %s\n", modbus_strerror(errno));
            modbus_free(modbusSensors[i].slave);
            exit(1);
        }
        modbusSensors[i].slaveNum = i+1;
        modbus_set_slave(modbusSensors[i].slave, modbusSensors[i].slaveNum);
    }

}

void ModbusDeInit(void)
{
    for(uint16_t i = 0u; i < numOfSlaves; i++)
    {
        modbus_close(modbusSensors[i].slave);
        modbus_free(modbusSensors[i].slave);
    }
}

void ModbusReadData(uint16_t slaveNum)
{
    int numOfReadRegs = modbus_read_registers(modbusSensors[slaveNum].slave, 0, NUM_OF_SLAVE_REGISTERS, modbusSensors[slaveNum].receivedData);
    if (numOfReadRegs != NUM_OF_SLAVE_REGISTERS) 
    {
        fprintf(stderr, "Failed to read: %s\n", modbus_strerror(errno));
    }
    else
    {
        printf("%i\n", modbusSensors[slaveNum].receivedData[0]);  
    }
}

