#include "dbg_led.h"
#include "stm32g4xx_ll_bus.h"
#include "stm32g4xx_ll_gpio.h"


#define LD1_Pin       LL_GPIO_PIN_4
#define LD1_GPIO_Port GPIOA

#define LD2_Pin       LL_GPIO_PIN_5
#define LD2_GPIO_Port GPIOA

void dbgLedsInit(void)
{
    LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);

    LL_GPIO_InitTypeDef gpioInitStruct = {
        .Pin        = LD1_Pin,
        .Mode       = LL_GPIO_MODE_OUTPUT,
        .Speed      = LL_GPIO_SPEED_MEDIUM,
        .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
        .Pull       = LL_GPIO_PULL_NO,
        .Alternate  = LL_GPIO_AF_0,
    };

    LL_GPIO_Init(LD1_GPIO_Port, &gpioInitStruct);

    gpioInitStruct.Pin = LD2_Pin;
    LL_GPIO_Init(LD2_GPIO_Port, &gpioInitStruct);
}

void dbgLed1On(void)
{
    LL_GPIO_SetOutputPin(LD2_GPIO_Port, LD2_Pin);
}
void dbgLed1Off(void)
{
    LL_GPIO_ResetOutputPin(LD2_GPIO_Port, LD2_Pin);
}
void dbgLed1Tog(void)
{
    LL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
}

void dbgLed2On(void)
{
    LL_GPIO_SetOutputPin(LD2_GPIO_Port, LD2_Pin);
}
void dbgLed2Off(void)
{
    LL_GPIO_ResetOutputPin(LD2_GPIO_Port, LD2_Pin);
}
void dbgLed2Tog(void)
{
    LL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
}