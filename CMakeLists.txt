cmake_minimum_required(VERSION 3.20)

include(cmake/emka_defaults.cmake)

project(CSHARK VERSION 1.0.0)

cmake_minimum_required(VERSION 3.20)
 
 
if("${TARGET_PLATFORM}" STREQUAL "EMBEDDED")

add_subdirectory(drivers)


add_library(freertos_config INTERFACE)
set(FREERTOS_CONFIG_INCLUDE_DIR freeRTOS_config)

target_include_directories(freertos_config SYSTEM
INTERFACE
    ${FREERTOS_CONFIG_INCLUDE_DIR}
)

target_compile_options(freertos_config INTERFACE ${ARM_CM4F_FLAGS})

set( FREERTOS_HEAP "4" CACHE STRING "" FORCE)
set( FREERTOS_PORT "GCC_ARM_CM4F" CACHE STRING "" FORCE)

add_subdirectory(FreeRTOS-Kernel)

set(APP_NAME cshark_test)
set(TARGET_MCU STM32G431xx)

set(FIRMWARE_VERSION_MAJOR ${CMAKE_PROJECT_VERSION_MAJOR})
set(FIRMWARE_VERSION_MINOR ${CMAKE_PROJECT_VERSION_MINOR})
set(FIRMWARE_VERSION_PATCH ${CMAKE_PROJECT_VERSION_PATCH})

set(CORE_SOURCES
    src/startup_stm32g431rbtx.s
    src/stm32g4xx_it.c
    src/syscalls.c
    src/sysmem.c
    src/system_stm32g4xx.c
    src/core_clock.c
    src/core_lpuart.c
    src/core_main.c
    dbg_led/dbg_led.c
    sensor.cpp
    uart_stm32.cpp
)

set(CORE_INCLUDE_DIRS
    .
    inc
    dbg_led
    user_button
)

add_arm_executable(${APP_NAME} main.cpp)

target_sources(${APP_NAME} PRIVATE 
    ${CORE_SOURCES}
)

target_include_directories(${APP_NAME} PRIVATE 
    ${CORE_INCLUDE_DIRS}
)


target_link_libraries(${APP_NAME} PRIVATE
    stm32_cube_G4
    freertos_config    
    freertos_kernel
)

target_compile_options(${APP_NAME}  PRIVATE
    -D${TARGET_MCU}
    ${ARM_CM4F_FLAGS}
    -DUSE_HAL_DRIVER

    -DCONSOLE_THREAD_SAFE=1
    ${ARM_DEFAULT_C_FLAGS}
    $<$<COMPILE_LANGUAGE:CXX>:${ARM_DEFAULT_CPP_FLAGS}>    
)

target_link_options(${APP_NAME} PRIVATE

    ${ARM_DEFAULT_LD_FLAGS}
    ${ARM_CM4F_FLAGS}
    -T${CMAKE_CURRENT_SOURCE_DIR}/stm32g431rbtx_flash.ld

)


elseif("${TARGET_PLATFORM}" STREQUAL "UNIT_TESTS")

add_unit_test(sensor_test_suite sensor_ut.cpp)
target_sources(sensor_test_suite PRIVATE sensor.cpp)
target_include_directories(sensor_test_suite PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

endif()



