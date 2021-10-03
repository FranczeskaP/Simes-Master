#ifndef POSTDATA_H
#define POSTDATA_H

#include <stdint.h>
#include "Modbus.h"

extern void InitCurl(void);

char * CreateStringToBePosted(DecodedData_t decodedData[numOfSlaves]);
extern void PerformPost(char * dataToPost);
extern void DeInitCurl(void);

#endif
