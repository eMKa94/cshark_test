#include "CppUTest/TestHarness.h"

#include <stdio.h>

#include "sensor.hpp"
#include "uart_mock.hpp"

UartMock uartMock;


// clang-format off
TEST_GROUP(SENSOR_TEST_SUITE)
{
    void teardown()
    {
        mock().checkExpectations();
        mock().clear();
    }
};
// clang-format on

TEST(SENSOR_TEST_SUITE, dummyTestShouldPass)
{
    CHECK_TRUE(true);
}

TEST(SENSOR_TEST_SUITE, temperatureSensorRead)
{
    TemperatureSensor          sensor(&uartMock);
    constexpr float            EXPECTED_TEMPERATURE = 23.4f;
    float                      temperature          = 0.0f;
    TemperatureSensor::error_E result               = TemperatureSensor::error_E::OK;

    // 23.4f  32 bit float little endian buffer is [ 0x33, 0x33, 0xBB, 0x41 ] . CRC = 0xD7

    mock().expectOneCall("sendByte").onObject(&uartMock).withUnsignedIntParameter("byte", 0xAA);
    mock().expectOneCall("getByte").onObject(&uartMock).andReturnValue(0x33);
    mock().expectOneCall("getByte").onObject(&uartMock).andReturnValue(0x33);
    mock().expectOneCall("getByte").onObject(&uartMock).andReturnValue(0xBB);
    mock().expectOneCall("getByte").onObject(&uartMock).andReturnValue(0x41);
    mock().expectOneCall("getByte").onObject(&uartMock).andReturnValue(0xD7);

    result = sensor.readTemperature(&temperature);
    CHECK_TRUE(result == TemperatureSensor::error_E::OK);
    DOUBLES_EQUAL(EXPECTED_TEMPERATURE, temperature, 0.02f);
}

TEST(SENSOR_TEST_SUITE, temperatureSensorRead_handleInvalidCRC)
{
    TemperatureSensor          sensor(&uartMock);
    constexpr float            EXPECTED_TEMPERATURE = 23.4f;
    float                      temperature          = 0.0f;
    TemperatureSensor::error_E result               = TemperatureSensor::error_E::OK;

    // 23.4f  32 bit float little endian buffer is [ 0x33, 0x33, 0xBB, 0x41 ] . CRC = 0xD7

    mock().expectOneCall("sendByte").onObject(&uartMock).withUnsignedIntParameter("byte", 0xAA);
    mock().expectOneCall("getByte").onObject(&uartMock).andReturnValue(0x33);
    mock().expectOneCall("getByte").onObject(&uartMock).andReturnValue(0x33);
    mock().expectOneCall("getByte").onObject(&uartMock).andReturnValue(0xBB);
    mock().expectOneCall("getByte").onObject(&uartMock).andReturnValue(0x41);
    mock().expectOneCall("getByte").onObject(&uartMock).andReturnValue(0xD9);

    result = sensor.readTemperature(&temperature);
    CHECK_TRUE(result == TemperatureSensor::error_E::CRC_ERROR);
}
