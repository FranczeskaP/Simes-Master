#ifndef POSTDATA_H
#define POSTDATA_H

#include <stdint.h>
#include "Decoder.h"
#include "DataTypes.h"

extern void InitCurl(void);
extern char * CreateStringToBePosted(void);
extern void PerformPost(char * dataToPost);
extern void DeInitCurl(void);

#endif
