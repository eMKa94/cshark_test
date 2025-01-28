#pragma once

#include "iuart.hpp"
#include "stdint.h"

class TemperatureSensor
{
public:
    enum class error_E
    {
        OK,
        COMMUNICATION_ERROR,
        CRC_ERROR
    };

    TemperatureSensor() = delete;
    TemperatureSensor(Iuart* pUart);
    ~TemperatureSensor() = default;

    error_E readTemperature(float* pTemp);

private:
    Iuart* mp_iUart = nullptr;

    static constexpr size_t SENSOR_DATA_FRAME_LENGTH = 5u;

    static constexpr uint8_t CRC_INIT = 0x00;
    static constexpr uint8_t CRC_POLY = 0x07;

    uint8_t calculateCrc(uint8_t* buff, size_t len);

    error_E getData(float* p_sensorData, uint8_t* p_crc);
};
