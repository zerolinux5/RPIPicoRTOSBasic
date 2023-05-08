cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(PICO_BOARD pico_w)

include (pico_sdk_import.cmake)

project(Pico-FreeRTOS)

pico_sdk_init()

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        -Wno-maybe-uninitialized
        )

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

add_subdirectory(lib/freertos/FreeRTOS-Kernel/portable/ThirdParty/GCC/RP2040 FreeRTOS-Kernel)
add_subdirectory(src)