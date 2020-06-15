#include "build/temp/_test_CircularBuffer.c"
#include "src/CircularBuffer.h"
#include "/var/lib/gems/2.7.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"


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

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((result)), (

   ((void *)0)

   ), (UNITY_UINT)(20), UNITY_DISPLAY_STYLE_INT);

}



void test_CircularBuffer_BufferSizeIsCorrectAfterCreation(void)

{

    CircularBuffer_Create(bufferSize);

    uint32_t realSize = CircularBuffer_getSize();

    UnityAssertEqualNumber((UNITY_INT)((bufferSize)), (UNITY_INT)((realSize)), (

   ((void *)0)

   ), (UNITY_UINT)(27), UNITY_DISPLAY_STYLE_INT);

}



void test_CircularBuffer_BufferDataInserionIsCorrect(void)

{

    int32_t sentData = 0xA5;

    CircularBuffer_InsertData(sentData);

    int32_t readData = CircularBuffer_GetNewestData();

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((sentData)), (UNITY_INT)(UNITY_INT16)((readData)), (

   ((void *)0)

   ), (UNITY_UINT)(35), UNITY_DISPLAY_STYLE_HEX16);

}



void test_CircularBuffer_BufferIsReturningNewestData(void)

{

    int32_t sentData = 0xA5;

    CircularBuffer_InsertData(sentData);

    sentData = 0x5A;

    CircularBuffer_InsertData(sentData);

    int32_t readData = CircularBuffer_GetNewestData();

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((sentData)), (UNITY_INT)(UNITY_INT16)((readData)), (

   ((void *)0)

   ), (UNITY_UINT)(45), UNITY_DISPLAY_STYLE_HEX16);

}



void test_CircularBuffer_BufferGetDataAtPosition(void)

{

    int32_t sentData[3] = {0xAA, 0xBB, 0xCC};

    int32_t readData = 0xFF;



    for (uint8_t i = 0; i < 3; i++) {

        CircularBuffer_InsertData(sentData[i]);

    }



    readData = CircularBuffer_getDataAtPosition(1);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0xBB)), (UNITY_INT)(UNITY_INT16)((readData)), (

   ((void *)0)

   ), (UNITY_UINT)(58), UNITY_DISPLAY_STYLE_HEX16);



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



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((sentData[2])), (UNITY_INT)(UNITY_INT16)((readData[0])), (

   ((void *)0)

   ), (UNITY_UINT)(74), UNITY_DISPLAY_STYLE_HEX16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((sentData[1])), (UNITY_INT)(UNITY_INT16)((readData[1])), (

   ((void *)0)

   ), (UNITY_UINT)(75), UNITY_DISPLAY_STYLE_HEX16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((sentData[0])), (UNITY_INT)(UNITY_INT16)((readData[2])), (

   ((void *)0)

   ), (UNITY_UINT)(76), UNITY_DISPLAY_STYLE_HEX16);

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



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((extraData)), (UNITY_INT)(UNITY_INT16)((readData[0])), (

   ((void *)0)

   ), (UNITY_UINT)(94), UNITY_DISPLAY_STYLE_HEX16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((sentData[2])), (UNITY_INT)(UNITY_INT16)((readData[1])), (

   ((void *)0)

   ), (UNITY_UINT)(95), UNITY_DISPLAY_STYLE_HEX16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((sentData[1])), (UNITY_INT)(UNITY_INT16)((readData[2])), (

   ((void *)0)

   ), (UNITY_UINT)(96), UNITY_DISPLAY_STYLE_HEX16);

}



void test_CircularBuffer_BufferClearAfterCreation(void)

{

    int32_t readData[3] = {0xFF, 0xFF, 0xFF};

    for (uint8_t i = 0; i < 3; i++) {

        readData[i] = CircularBuffer_getDataAtPosition(i);

        UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((readData[i])), (

       ((void *)0)

       ), (UNITY_UINT)(104), UNITY_DISPLAY_STYLE_INT);

    }

}
