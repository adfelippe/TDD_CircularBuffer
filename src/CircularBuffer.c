#include "CircularBuffer.h"

static int32_t *buffer;
static uint32_t bufferSize = -1;

int8_t CircularBuffer_Create(uint32_t size)
{
    buffer = (int*)calloc(sizeof(buffer), size);
    if (buffer == NULL) {
        return -1;
    } else {
        bufferSize = size;
        return 0;
    }
}

uint32_t CircularBuffer_getSize(void)
{
    return bufferSize;
}

void CircularBuffer_Destroy(void)
{
    free(buffer);
}

void CircularBuffer_InsertData(int32_t data)
{
    for (uint32_t i = (bufferSize - 1); i > 0; i--) {
        buffer[i] = buffer[i - 1];
    }
    buffer[0] = data;
}

int32_t CircularBuffer_GetNewestData(void)
{
    return buffer[0];
}

int32_t CircularBuffer_getDataAtPosition(uint32_t position)
{
    return buffer[position];
}
