#include "core_lpuart.h"
#include "stm32g4xx_ll_bus.h"
#include "stm32g4xx_ll_gpio.h"
#include "stm32g4xx_ll_lpuart.h"
#include "stm32g4xx_ll_rcc.h"

#define LPUART1_TX_Pin       LL_GPIO_PIN_2
#define LPUART1_TX_GPIO_Port GPIOA
#define LPUART1_RX_Pin       LL_GPIO_PIN_3
#define LPUART1_RX_GPIO_Port GPIOA

e_lpuartErr_t coreLpuartInit(void)
{

    LL_LPUART_InitTypeDef LPUART_InitStruct = {0};

    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    LL_RCC_SetLPUARTClockSource(LL_RCC_LPUART1_CLKSOURCE_PCLK1);

    LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_LPUART1);

    LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);

    GPIO_InitStruct.Pin        = LPUART1_TX_Pin;
    GPIO_InitStruct.Mode       = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed      = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull       = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Alternate  = LL_GPIO_AF_12;
    LL_GPIO_Init(LPUART1_TX_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin        = LPUART1_RX_Pin;
    GPIO_InitStruct.Mode       = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed      = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull       = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Alternate  = LL_GPIO_AF_12;
    LL_GPIO_Init(LPUART1_RX_GPIO_Port, &GPIO_InitStruct);

    LPUART_InitStruct.PrescalerValue      = LL_LPUART_PRESCALER_DIV1;
    LPUART_InitStruct.BaudRate            = 115200;
    LPUART_InitStruct.DataWidth           = LL_LPUART_DATAWIDTH_8B;
    LPUART_InitStruct.StopBits            = LL_LPUART_STOPBITS_1;
    LPUART_InitStruct.Parity              = LL_LPUART_PARITY_NONE;
    LPUART_InitStruct.TransferDirection   = LL_LPUART_DIRECTION_TX_RX;
    LPUART_InitStruct.HardwareFlowControl = LL_LPUART_HWCONTROL_NONE;
    LL_LPUART_Init(LPUART1, &LPUART_InitStruct);
    LL_LPUART_SetTXFIFOThreshold(LPUART1, LL_LPUART_FIFOTHRESHOLD_1_8);
    LL_LPUART_SetRXFIFOThreshold(LPUART1, LL_LPUART_FIFOTHRESHOLD_1_8);
    LL_LPUART_DisableFIFO(LPUART1);

    // LL_LPUART_EnableIT_RXNE_RXFNE(LPUART1); // Enable RXNE and RXFNE interrupts

    LL_LPUART_Enable(LPUART1);

    while ((!(LL_LPUART_IsActiveFlag_TEACK(LPUART1))) || (!(LL_LPUART_IsActiveFlag_REACK(LPUART1))))
    {
    }

    return LPU_OK;
}

e_lpuartErr_t coreLpuartSendByte(uint8_t byte)
{

    while (!LL_LPUART_IsActiveFlag_TC(LPUART1))
    {
    }
    LL_LPUART_TransmitData8(LPUART1, byte);

    return LPU_OK;
}

bool coreLpuartIsByteReceived(void)
{
    return LL_LPUART_IsActiveFlag_RXNE(LPUART1);
}

char coreLpuartReceiveByte(void)
{
    return LL_LPUART_ReceiveData8(LPUART1);
}