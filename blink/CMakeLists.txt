cmake_minimum_required(VERSION 3.13)
set(ENV{PICO_SDK_PATH} "D:/Anudeep_Workspace/Workspace/FreeRTOS/freertos-pico/pico-sdk")
set(ENV{FREERTOS_KERNEL_PATH} "D:/Anudeep_Workspace/Workspace/FreeRTOS/freertos-pico/pico-sdk/FreeRTOS-Kernel")
#set(CMAKE_MAKE_PROGRAM "C:/MinGW/bin")

SET(CMAKE_C_COMPILER_WORKS TRUE CACHE INTERNAL "")
SET(CMAKE_CXX_COMPILER_WORKS TRUE CACHE INTERNAL "") #sqaush the compiler tests

# Pull in SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
message("print Test " )

# Pull in FreeRTOS
include($ENV{FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)


project(app C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

add_executable(blink main.cpp)

target_include_directories(blink PRIVATE ${CMAKE_CURRENT_LIST_DIR})
 
# pull in common dependencies
target_link_libraries(blink pico_stdlib FreeRTOS-Kernel FreeRTOS-Kernel-Heap4)

pico_enable_stdio_usb(blink 1)
pico_enable_stdio_uart(blink 0)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(blink)
