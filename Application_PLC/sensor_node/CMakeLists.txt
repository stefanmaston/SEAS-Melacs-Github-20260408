cmake_minimum_required(VERSION 3.13)

if(NOT DEFINED PICO_SDK_PATH)
    message(FATAL_ERROR "Sätt PICO_SDK_PATH till Pico SDK")
endif()

include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(sensor_node C CXX ASM)
set(CMAKE_C_STANDARD 11)
pico_sdk_init()

add_executable(sensor_node
    src/port_pico.c
    src/node_logic.c
    src/node_display.c
    ../shared/modbus_rtu.c
)

target_include_directories(sensor_node PRIVATE include ../shared)
target_link_libraries(sensor_node
    pico_stdlib
    hardware_spi
    hardware_i2c
    hardware_adc
    hardware_uart
)

pico_enable_stdio_uart(sensor_node 0)
pico_add_extra_outputs(sensor_node)
