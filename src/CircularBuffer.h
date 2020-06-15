#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#include <stdint.h>
#include <stdlib.h>

int8_t CircularBuffer_Create(uint32_t size);
void CircularBuffer_Destroy(void);
uint32_t CircularBuffer_getSize(void);
void CircularBuffer_InsertData(int32_t data);
int32_t CircularBuffer_GetNewestData(void);
int32_t CircularBuffer_getDataAtPosition(uint32_t position);

#endif // CIRCULARBUFFER_H
