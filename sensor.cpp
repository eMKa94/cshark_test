#include "sensor.hpp"
#include <stddef.h>
#include <string.h>

TemperatureSensor::TemperatureSensor(Iuart* pUart) : mp_iUart(pUart)
{
}

TemperatureSensor::error_E TemperatureSensor::readTemperature(float* pTemp)

{
    uint8_t          dataBuffer[SENSOR_DATA_FRAME_LENGTH] = {};
    volatile uint8_t crc                                  = 0;

    // 0xAA == "get data" request
    mp_iUart->sendByte(0xAA);

    for (uint8_t i = 0; i < SENSOR_DATA_FRAME_LENGTH; i++)
    {
        dataBuffer[i] = mp_iUart->getByte();
    }

    crc = dataBuffer[4];

    uint8_t calculatedCrc = calculateCrc(dataBuffer, 4);
    if (calculatedCrc != crc)
    {
        return error_E::CRC_ERROR;
    }

    memcpy(pTemp, dataBuffer, 4);

    return error_E::OK;
}


uint8_t TemperatureSensor::calculateCrc(uint8_t* buff, size_t len)
{
    uint8_t crc = CRC_INIT;

    while (len--)
    {
        crc ^= *buff++; // XOR byte into the CRC register
        for (uint8_t i = 0; i < 8; i++)
        {
            crc = (crc & 0x80) ? (crc << 1) ^ CRC_POLY : (crc << 1);
        }
    }

    return crc;
}