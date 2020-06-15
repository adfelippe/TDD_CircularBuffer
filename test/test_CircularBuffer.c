#include "unity.h"
#include "CircularBuffer.h"

uint32_t bufferSize;

void setUp(void)
{
    bufferSize = 3;
    CircularBuffer_Create(bufferSize);
}

void tearDown(void)
{
    CircularBuffer_Destroy();
}

void test_CircularBuffer_BufferIsCreatedCorrectly(void)
{
    int8_t result = CircularBuffer_Create(bufferSize);
    TEST_ASSERT_EQUAL(0, result);
}

void test_CircularBuffer_BufferSizeIsCorrectAfterCreation(void)
{
    CircularBuffer_Create(bufferSize);
    uint32_t realSize = CircularBuffer_getSize();
    TEST_ASSERT_EQUAL(bufferSize, realSize);
}

void test_CircularBuffer_BufferDataInserionIsCorrect(void)
{
    int32_t sentData = 0xA5;
    CircularBuffer_InsertData(sentData);
    int32_t readData = CircularBuffer_GetNewestData();
    TEST_ASSERT_EQUAL_HEX16(sentData, readData);
}

void test_CircularBuffer_BufferIsReturningNewestData(void)
{
    int32_t sentData = 0xA5;
    CircularBuffer_InsertData(sentData);
    sentData = 0x5A;
    CircularBuffer_InsertData(sentData);
    int32_t readData = CircularBuffer_GetNewestData();
    TEST_ASSERT_EQUAL_HEX16(sentData, readData);
}

void test_CircularBuffer_BufferGetDataAtPosition(void)
{
    int32_t sentData[3] = {0xAA, 0xBB, 0xCC};
    int32_t readData = 0xFF;

    for (uint8_t i = 0; i < 3; i++) {
        CircularBuffer_InsertData(sentData[i]);
    }

    readData = CircularBuffer_getDataAtPosition(1);
    TEST_ASSERT_EQUAL_HEX16(0xBB, readData);

}

void test_CircularBuffer_BufferIsCirculating(void)
{
    int32_t sentData[3] = {0xAA, 0xBB, 0xCC};
    int32_t readData[3] = {0xFF, 0xFF, 0xFF};

    for (uint8_t i = 0; i < 3; i++) {
        CircularBuffer_InsertData(sentData[i]);
    }
    for (uint8_t i = 0; i < 3; i++) {
        readData[i] = CircularBuffer_getDataAtPosition(i);
    }

    TEST_ASSERT_EQUAL_HEX16(sentData[2], readData[0]);
    TEST_ASSERT_EQUAL_HEX16(sentData[1], readData[1]);
    TEST_ASSERT_EQUAL_HEX16(sentData[0], readData[2]);
}

void test_CircularBuffer_BufferIsRotating(void)
{
    int32_t sentData[3] = {0xAA, 0xBB, 0xCC};
    int32_t readData[3] = {0xFF, 0xFF, 0xFF};
    int32_t extraData = 0xDD;

    for (uint8_t i = 0; i < 3; i++) {
        CircularBuffer_InsertData(sentData[i]);
    }
    CircularBuffer_InsertData(extraData);

    for (uint8_t i = 0; i < 3; i++) {
        readData[i] = CircularBuffer_getDataAtPosition(i);
    }

    TEST_ASSERT_EQUAL_HEX16(extraData, readData[0]);
    TEST_ASSERT_EQUAL_HEX16(sentData[2], readData[1]);
    TEST_ASSERT_EQUAL_HEX16(sentData[1], readData[2]);
}

void test_CircularBuffer_BufferClearAfterCreation(void)
{
    int32_t readData[3] = {0xFF, 0xFF, 0xFF};
    for (uint8_t i = 0; i < 3; i++) {
        readData[i] = CircularBuffer_getDataAtPosition(i);
        TEST_ASSERT_EQUAL(0, readData[i]);
    }
}
