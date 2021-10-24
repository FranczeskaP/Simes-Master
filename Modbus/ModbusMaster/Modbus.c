#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "Modbus.h"

#define DEVICE_NAME             ("/dev/ttyUSB0")
#define BAUDRATE                (9600u)
#define PARITY                  ('N')
#define DATA_BITS               (8u)
#define STOP_BITS               (1u)

ModbusData_t modbusSensors[numOfSlaves];
static uint8_t ModbusReadData(uint16_t slaveNum, uint16_t address, uint16_t numOfRegisters);

void ModbusInit(void)
{
    struct timeval response_timeout;
    response_timeout.tv_sec = 1;
    response_timeout.tv_usec = 0;
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
        modbus_set_response_timeout(modbusSensors[i].slave, response_timeout.tv_sec, response_timeout.tv_usec);
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

uint8_t ModubsReadDcData(void)
{
    uint8_t error = 0u;
    if(sensorid1.communicaion = modbus)
    {
        error |= ModbusReadData(1, 0u, NUM_OF_SLAVE_REGISTERS);
    }
    if(sensorid2.communicaion = modbus)
    {
        error |= ModbusReadData(2, 0u, NUM_OF_SLAVE_REGISTERS);
    }
    if(sensorid3.communicaion = modbus)
    {
        error |= ModbusReadData(3, 0u, NUM_OF_SLAVE_REGISTERS);
    }
    if(sensorid4.communicaion = modbus)
    {
        error |= ModbusReadData(4, 0u, NUM_OF_SLAVE_REGISTERS);
    }
    return error;
}

static uint8_t ModbusReadData(uint16_t slaveNum, uint16_t address, uint16_t numOfRegisters)
{
    uint8_t error = 0u;
    int numOfReadRegs = modbus_read_input_registers(modbusSensors[slaveNum-1].slave, address, numOfRegisters, modbusSensors[slaveNum-1].receivedData);
    if (numOfReadRegs != numOfRegisters) 
    {
        error = 1u;
        fprintf(stderr, "Failed to read: %s\n", modbus_strerror(errno));
    }
    return error;
}
