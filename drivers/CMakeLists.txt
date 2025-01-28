cmake_minimum_required(VERSION 3.20)


set(CMSIS_PATH STM32CubeG4/Drivers/CMSIS)
set(HAL_PATH STM32CubeG4/Drivers/STM32G4xx_HAL_Driver)
set(FREERTOS_PATH STM32CubeG4/Middlewares/Third_Party/FreeRTOS/Source)
set(STM32_USB_PATH STM32CubeG4/Middlewares/ST/STM32_USB_Device_Library)

set(CORE_SOURCES 

    ${HAL_PATH}/Src/stm32g4xx_hal_adc.c
    ${HAL_PATH}/Src/stm32g4xx_hal_adc_ex.c
    ${HAL_PATH}/Src/stm32g4xx_hal.c
    ${HAL_PATH}/Src/stm32g4xx_hal_comp.c
    ${HAL_PATH}/Src/stm32g4xx_hal_cordic.c
    ${HAL_PATH}/Src/stm32g4xx_hal_cortex.c
    ${HAL_PATH}/Src/stm32g4xx_hal_crc.c
    ${HAL_PATH}/Src/stm32g4xx_hal_crc_ex.c
    ${HAL_PATH}/Src/stm32g4xx_hal_cryp.c
    ${HAL_PATH}/Src/stm32g4xx_hal_cryp_ex.c
    ${HAL_PATH}/Src/stm32g4xx_hal_dac.c
    ${HAL_PATH}/Src/stm32g4xx_hal_dac_ex.c
    ${HAL_PATH}/Src/stm32g4xx_hal_dma.c
    ${HAL_PATH}/Src/stm32g4xx_hal_dma_ex.c
    ${HAL_PATH}/Src/stm32g4xx_hal_exti.c
    ${HAL_PATH}/Src/stm32g4xx_hal_fdcan.c
    ${HAL_PATH}/Src/stm32g4xx_hal_flash.c
    ${HAL_PATH}/Src/stm32g4xx_hal_flash_ex.c
    ${HAL_PATH}/Src/stm32g4xx_hal_flash_ramfunc.c
    ${HAL_PATH}/Src/stm32g4xx_hal_fmac.c
    ${HAL_PATH}/Src/stm32g4xx_hal_gpio.c
    ${HAL_PATH}/Src/stm32g4xx_hal_hrtim.c
    ${HAL_PATH}/Src/stm32g4xx_hal_i2c.c
    ${HAL_PATH}/Src/stm32g4xx_hal_i2c_ex.c
    ${HAL_PATH}/Src/stm32g4xx_hal_i2s.c
    ${HAL_PATH}/Src/stm32g4xx_hal_irda.c
    ${HAL_PATH}/Src/stm32g4xx_hal_iwdg.c
    ${HAL_PATH}/Src/stm32g4xx_hal_lptim.c
    # ${HAL_PATH}/Src/stm32g4xx_hal_msp_template.c
    ${HAL_PATH}/Src/stm32g4xx_hal_nand.c
    ${HAL_PATH}/Src/stm32g4xx_hal_nor.c
    ${HAL_PATH}/Src/stm32g4xx_hal_opamp.c
    ${HAL_PATH}/Src/stm32g4xx_hal_opamp_ex.c
    ${HAL_PATH}/Src/stm32g4xx_hal_pcd.c
    ${HAL_PATH}/Src/stm32g4xx_hal_pcd_ex.c
    ${HAL_PATH}/Src/stm32g4xx_hal_pwr.c
    ${HAL_PATH}/Src/stm32g4xx_hal_pwr_ex.c
    ${HAL_PATH}/Src/stm32g4xx_hal_qspi.c
    ${HAL_PATH}/Src/stm32g4xx_hal_rcc.c
    ${HAL_PATH}/Src/stm32g4xx_hal_rcc_ex.c
    ${HAL_PATH}/Src/stm32g4xx_hal_rng.c
    ${HAL_PATH}/Src/stm32g4xx_hal_rtc.c
    ${HAL_PATH}/Src/stm32g4xx_hal_rtc_ex.c
    ${HAL_PATH}/Src/stm32g4xx_hal_sai.c
    ${HAL_PATH}/Src/stm32g4xx_hal_sai_ex.c
    ${HAL_PATH}/Src/stm32g4xx_hal_smartcard.c
    ${HAL_PATH}/Src/stm32g4xx_hal_smartcard_ex.c
    ${HAL_PATH}/Src/stm32g4xx_hal_smbus.c
    ${HAL_PATH}/Src/stm32g4xx_hal_smbus_ex.c
    ${HAL_PATH}/Src/stm32g4xx_hal_spi.c
    ${HAL_PATH}/Src/stm32g4xx_hal_spi_ex.c
    ${HAL_PATH}/Src/stm32g4xx_hal_sram.c
    ${HAL_PATH}/Src/stm32g4xx_hal_tim.c
    # ${HAL_PATH}/Src/stm32g4xx_hal_timebase_tim_template.c
    ${HAL_PATH}/Src/stm32g4xx_hal_tim_ex.c
    ${HAL_PATH}/Src/stm32g4xx_hal_uart.c
    ${HAL_PATH}/Src/stm32g4xx_hal_uart_ex.c
    ${HAL_PATH}/Src/stm32g4xx_hal_usart.c
    ${HAL_PATH}/Src/stm32g4xx_hal_usart_ex.c
    ${HAL_PATH}/Src/stm32g4xx_hal_wwdg.c
    ${HAL_PATH}/Src/stm32g4xx_ll_adc.c
    ${HAL_PATH}/Src/stm32g4xx_ll_comp.c
    ${HAL_PATH}/Src/stm32g4xx_ll_cordic.c
    ${HAL_PATH}/Src/stm32g4xx_ll_crc.c
    ${HAL_PATH}/Src/stm32g4xx_ll_crs.c
    ${HAL_PATH}/Src/stm32g4xx_ll_dac.c
    ${HAL_PATH}/Src/stm32g4xx_ll_dma.c
    ${HAL_PATH}/Src/stm32g4xx_ll_exti.c
    ${HAL_PATH}/Src/stm32g4xx_ll_fmac.c
    # ${HAL_PATH}/Src/stm32g4xx_ll_fmc.c
    ${HAL_PATH}/Src/stm32g4xx_ll_gpio.c
    ${HAL_PATH}/Src/stm32g4xx_ll_hrtim.c
    ${HAL_PATH}/Src/stm32g4xx_ll_i2c.c
    ${HAL_PATH}/Src/stm32g4xx_ll_lptim.c
    ${HAL_PATH}/Src/stm32g4xx_ll_lpuart.c
    ${HAL_PATH}/Src/stm32g4xx_ll_opamp.c
    ${HAL_PATH}/Src/stm32g4xx_ll_pwr.c
    ${HAL_PATH}/Src/stm32g4xx_ll_rcc.c
    ${HAL_PATH}/Src/stm32g4xx_ll_rng.c
    ${HAL_PATH}/Src/stm32g4xx_ll_rtc.c
    ${HAL_PATH}/Src/stm32g4xx_ll_spi.c
    ${HAL_PATH}/Src/stm32g4xx_ll_tim.c
    ${HAL_PATH}/Src/stm32g4xx_ll_ucpd.c
    ${HAL_PATH}/Src/stm32g4xx_ll_usart.c
    ${HAL_PATH}/Src/stm32g4xx_ll_usb.c
    ${HAL_PATH}/Src/stm32g4xx_ll_utils.c


)

set(CORE_INCLUDE_DIRS

    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMSIS_PATH}/Include
    ${CMSIS_PATH}/Core/Include
    ${CMSIS_PATH}/Device/ST/STM32G4xx/Include
    ${HAL_PATH}/Inc


)

add_library(stm32_cube_G4 INTERFACE)
target_sources(stm32_cube_G4 INTERFACE ${CORE_SOURCES})
target_include_directories(stm32_cube_G4 INTERFACE ${CORE_INCLUDE_DIRS})
