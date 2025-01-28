#pragma once

#include "CppUTestExt/MockSupport.h"

#include "iuart.hpp"

class UartMock : public Iuart
{
public:
    UartMock()  = default;
    ~UartMock() = default;

    virtual void sendByte(uint8_t byte) override
    {
        mock().actualCall("sendByte").onObject(this).withUnsignedIntParameter("byte", byte);
    }
    virtual void sendBuffer(uint8_t* buff, size_t len) override
    {
        mock().actualCall("sendBuffer").onObject(this);
    }
    virtual uint8_t getByte() override
    {
        return mock().actualCall("getByte").onObject(this).returnUnsignedIntValue();
    }
};