// #include "cmsis_os.h"
#include "core_clock.h"
#include "core_lpuart.h"
#include "core_main.h"

#include "stm32g4xx_hal.h"
#include "stm32g4xx_ll_bus.h"

#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

#include "dbg_led.h"
#include "sensor.hpp"
#include "uart_stm32.hpp"

#include <stdio.h>
#include <string.h>

void dataReadingTask(void* argument);
void dataProcessingTask(void* argument);

void Error_Handler(void);
void spiInit(void);

QueueHandle_t    sensorDataQueue        = NULL;
constexpr size_t SENSOR_DATA_QUEUE_SIZE = 1u;


extern "C" int main()
{

    UartStm lpUart;

    HAL_Init();

    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
    LL_AHB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

    HAL_PWREx_DisableUCPDDeadBattery();

    if (coreClockInit() != CLK_OK)
    {
        Error_Handler();
    }

    lpUart.init();

    dbgLedsInit();

    sensorDataQueue = xQueueCreate(SENSOR_DATA_QUEUE_SIZE, sizeof(float));
    if (sensorDataQueue == NULL)
    {
        Error_Handler();
    }

    xTaskCreate(dataReadingTask, "reading", 1024, &lpUart, tskIDLE_PRIORITY, NULL);
    xTaskCreate(dataProcessingTask, "processing", 1024, NULL, tskIDLE_PRIORITY, NULL);

    vTaskStartScheduler();

    while (1)
    {
    }

    return 0;
}

void dataReadingTask(void* argument)
{
    TemperatureSensor          sensor((Iuart*)argument);
    TemperatureSensor::error_E result      = TemperatureSensor::error_E::OK;
    float                      temperature = 0.0f;

    while (1)
    {
        result = sensor.readTemperature(&temperature);
        if (result == TemperatureSensor::error_E::OK)
        {
            // TODO: queueSend error handling...
            xQueueSend(sensorDataQueue, &temperature, 1000);
        }
        vTaskDelay(1000);
    }
}


void dataProcessingTask(void* argument)
{
    float   samplesBuffer[10] = {0.0f};
    float   filteredData      = 0.0f;
    uint8_t index             = 0;

    while (1)
    {
        // TODO: queuePeak error handling...
        xQueuePeek(sensorDataQueue, &samplesBuffer[index], portMAX_DELAY);
        dbgLed1On(); // Indicate data received

        // Simple moving average filtering
        filteredData = 0.0f;
        for (uint8_t i = 0; i < 10; i++)
        {
            filteredData += samplesBuffer[i];
        }
        filteredData = filteredData / 10.0f;

        dbgLed2On(); // Indicate data processed;
    }
}

void Error_Handler(void)
{
    // TODO: Error handler callback from application
    __disable_irq();
    while (1)
    {
    }
}

extern "C" void vApplicationStackOverflowHook(TaskHandle_t xTask, char* pcTaskName)
{
    // LOG("Stack overflow in [ %s ]", pcTaskName);
}

extern "C" void vApplicationIdleHook(void)
{
}

// CM4 FreeRTOS port does not provide sys tick ISR. Application should manage it explicitly.
extern "C" void xPortSysTickHandler(void);
extern "C" void SysTick_Handler(void)
{
    /* Clear overflow flag */
    SysTick->CTRL;

    if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
    {
        /* Call tick handler */
        xPortSysTickHandler();
    }
}