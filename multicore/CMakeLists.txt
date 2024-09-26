cmake_minimum_required(VERSION 3.13)
set(ENV{PICO_SDK_PATH} "D:/Anudeep_Workspace/Workspace/FreeRTOS/freertos-pico/pico-sdk-fork/pico-sdk")
set(ENV{FREERTOS_KERNEL_PATH} "D:/Anudeep_Workspace/Workspace/FreeRTOS/freertos-pico/pico-sdk-fork/pico-sdk/FreeRTOS-Kernel")
#set(CMAKE_MAKE_PROGRAM "C:/MinGW/bin")

SET(CMAKE_C_COMPILER_WORKS TRUE CACHE INTERNAL "")
SET(CMAKE_CXX_COMPILER_WORKS TRUE CACHE INTERNAL "") #sqaush the compiler tests

# Pull in SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
message("print Test " )

# Pull in FreeRTOS
#include($ENV{FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)


project(multicore C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

add_executable(multicore main.cpp)

target_include_directories(multicore PRIVATE ${CMAKE_CURRENT_LIST_DIR})
 
# pull in common dependencies
target_link_libraries(multicore
     pico_stdlib
     pico_multicore
     hardware_adc)

pico_enable_stdio_usb(multicore 1)
pico_enable_stdio_uart(multicore 0)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(multicore)
