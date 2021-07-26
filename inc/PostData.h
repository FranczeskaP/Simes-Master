#ifndef POSTDATA_H
#define POSTDATA_H

#include <stdint.h>

extern void InitCurl(void);
extern void PerformPost(char * dataToPost);
extern void DeInitCurl(void);

#endif
