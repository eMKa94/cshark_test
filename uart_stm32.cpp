#include "uart_stm32.hpp"
#include "core_lpuart.h"

void UartStm::init()
{
    coreLpuartInit();
}
void UartStm::sendByte(uint8_t byte)
{
    coreLpuartSendByte(byte);
}

void UartStm::sendBuffer(uint8_t* buff, size_t len)
{
    for (size_t i = 0; i < len; i++)
        sendByte(*buff++);
}

uint8_t UartStm::getByte()
{
    return (uint8_t)coreLpuartReceiveByte();
}
