#pragma once

#include <stddef.h>
#include <stdint.h>

class Iuart
{
public:
    virtual void    sendByte(uint8_t byte)                = 0;
    virtual void    sendBuffer(uint8_t* buff, size_t len) = 0;
    virtual uint8_t getByte()                             = 0;
};