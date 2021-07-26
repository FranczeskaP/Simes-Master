#ifndef POSTDATA_H
#define POSTDATA_H

#include <stdint.h>

extern uint16_t InitCurl(void);
extern void PerformPost(DecodedData_t * decodedData);
extern void DeInitCurl(void);

#endif
