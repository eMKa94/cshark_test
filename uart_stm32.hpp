#pragma once

#include "iuart.hpp"

class UartStm : public Iuart
{
public:
    UartStm()  = default;
    ~UartStm() = default;

    virtual void    sendByte(uint8_t byte) override;
    virtual void    sendBuffer(uint8_t* buff, size_t len) override;
    virtual uint8_t getByte() override;

    void init(void);
};