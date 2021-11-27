#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include "Modbus.h"
#include "Configuration.h"

#define DEVICE_NAME             ("/dev/ttyUSB0")
#define BAUDRATE                (9600u)
#define PARITY                  ('N')
#define DATA_BITS               (8u)
#define STOP_BITS               (1u)
#define TIME_MS_MODBUS          (2u)

ModbusData_t modbusSensors;
ModbusDataDc_t modbusDcSensors[numOfDcSlaves];
static struct timespec WaitTimeModbus = {
    .tv_sec = 0,
    .tv_nsec = TIME_MS_MODBUS * 1000000
};
static struct timeval response_timeout = {
    .tv_sec = 1,
    .tv_usec = 0
};

static uint8_t modbusReadDc(uint16_t slaveNum);
static uint8_t modbusReadAc(void);
static void initDcModbus(void);
static void initAcModbus(void);

void ModbusInit(void)
{
    initDcModbus();
    initAcModbus();
}

void ModbusDeInit(void)
{
    for(uint16_t i = 0u; i < numOfDcSlaves; i++)
    {
        modbus_close(modbusSensors.dcSensors[i].slave);
        modbus_free(modbusSensors.dcSensors[i].slave);
    }
    modbus_close(modbusSensors.acSensor.slave);
    modbus_free(modbusSensors.acSensor.slave);
}

uint8_t ModubsReadData(void)
{
    uint8_t error = 0u;
    for(uint8_t i = 0u; i < MAX_NUM_OF_SENSORS; i++)
    {
        if(configurationData[i].communicationProtocol = Modbus)
        {
            if((configurationData[i].id != 255u) && (!configurationData[i].acSensor))
            {
                error |= modbusReadDc(configurationData[i].id);
            }
            else if((configurationData[i].id != 255u) && (configurationData[i].acSensor))
            {
                error |= modbusReadAc();
            }
        }
    }

    return error;
}

static uint8_t modbusReadDc(uint16_t slaveNum)
{
    uint8_t error = 0u;
    int numOfReadRegs = modbus_read_input_registers(modbusSensors.dcSensors[slaveNum-1].slave, 0u, NUM_OF_DC_REGISTERS, modbusSensors.dcSensors[slaveNum-1].receivedData);
    if (numOfReadRegs != NUM_OF_DC_REGISTERS) 
    {
        error = 1u;
        fprintf(stderr, "Failed to read: %s\n", modbus_strerror(errno));
    }
    nanosleep(&WaitTimeModbus, &WaitTimeModbus);
    return error;
}

static uint8_t modbusReadAc(void)
{
    uint8_t error = 0u;
    int numOfReadRegs = modbus_read_input_registers(modbusSensors.acSensor.slave, 0u, NUM_OF_AC_REGISTERS, modbusSensors.acSensor.receivedData);
    if (numOfReadRegs != NUM_OF_AC_REGISTERS) 
    {
        error = 1u;
        fprintf(stderr, "Failed to read: %s\n", modbus_strerror(errno));
    }
    nanosleep(&WaitTimeModbus, &WaitTimeModbus);
    return error;
}

static void initDcModbus(void)
{
    for(uint16_t i = 0u; i < numOfDcSlaves; i++)
    {
        modbusSensors.dcSensors[i].slave = modbus_new_rtu(DEVICE_NAME, BAUDRATE, PARITY, DATA_BITS, STOP_BITS);
        if (!modbusSensors.dcSensors[i].slave) 
        {
            fprintf(stderr, "Failed to create the context: %s\n", modbus_strerror(errno));
            exit(1);
        }

        if (modbus_connect(modbusSensors.dcSensors[i].slave) == -1) 
        {
            fprintf(stderr, "Unable to connect: %s\n", modbus_strerror(errno));
            modbus_free(modbusSensors.dcSensors[i].slave);
            exit(1);
        }
        modbusSensors.dcSensors[i].slaveNum = i+1;
        modbus_set_response_timeout(modbusSensors.dcSensors[i].slave, response_timeout.tv_sec, response_timeout.tv_usec);
        modbus_set_slave(modbusSensors.dcSensors[i].slave, modbusSensors.dcSensors[i].slaveNum);
    }
}

static void initAcModbus(void)
{
    modbusSensors.acSensor.slave = modbus_new_rtu(DEVICE_NAME, BAUDRATE, PARITY, DATA_BITS, STOP_BITS);
    if (!modbusSensors.acSensor.slave) 
    {
        fprintf(stderr, "Failed to create the context: %s\n", modbus_strerror(errno));
        exit(1);
    }

    if (modbus_connect(modbusSensors.acSensor.slave) == -1) 
    {
        fprintf(stderr, "Unable to connect: %s\n", modbus_strerror(errno));
        modbus_free(modbusSensors.acSensor.slave);
        exit(1);
    }
    modbusSensors.acSensor.slaveNum = 0u;
    modbus_set_response_timeout(modbusSensors.acSensor.slave, response_timeout.tv_sec, response_timeout.tv_usec);
    modbus_set_slave(modbusSensors.acSensor.slave, modbusSensors.acSensor.slaveNum);
}
