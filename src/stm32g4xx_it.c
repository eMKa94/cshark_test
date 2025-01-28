#include "stm32g4xx_it.h"
#include "core_main.h"

void NMI_Handler(void)
{
    while (1)
    {
    }
}

void HardFault_Handler(void)
{
    while (1)
    {
    }
}

void MemManage_Handler(void)
{
    while (1)
    {
    }
}

void BusFault_Handler(void)
{
    while (1)
    {
    }
}

void UsageFault_Handler(void)
{
    while (1)
    {
    }
}

/**
 * @brief This function handles Debug monitor.
 */
void DebugMon_Handler(void)
{
}

void USB_LP_IRQHandler(void)
{
    // HAL_PCD_IRQHandler(&hpcd_USB_FS);
}

void TIM1_UP_TIM16_IRQHandler(void)
{
    // HAL_TIM_IRQHandler(&htim1);
}
