#ifndef POSTDATA_H
#define POSTDATA_H

#include <stdint.h>
#include "Decoder.h"

extern void InitCurl(void);
extern char * CreateStringToBePostedModbus(DecodedData_t decodedData[numOfDcSlaves]);
extern void PerformPost(char * dataToPost);
extern void DeInitCurl(void);

#endif
