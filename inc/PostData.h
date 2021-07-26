#ifndef POSTDATA_H
#define POSTDATA_H

#include <stdint.h>

extern uint16_t InitCurl(char *dataToPost);
extern void PerformPost(char *dataToPost);
extern void DeInitCurl(void);

#endif
