# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion RISCV_ZCB_RPI_2_2_0_3)
set(picotoolVersion 2.2.0-a4)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico2 CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(Gakushu_Bare C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1
# 1. 実行ファイルに使用する全ファイルをリストアップ
add_executable(Gakushu_Bare
    main.cpp
    driver/sht31/SHT31.cpp
    lib/pico-ssd1306/ssd1306.cpp
    lib/pico-ssd1306/frameBuffer/FrameBuffer.cpp
    lib/pico-ssd1306/textRenderer/TextRenderer.cpp
)

pico_set_program_name(Gakushu_Bare "Gakushu_Bare")
pico_set_program_version(Gakushu_Bare "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(Gakushu_Bare 0)
pico_enable_stdio_usb(Gakushu_Bare 1)

# Add the standard include files to the build
target_include_directories(Gakushu_Bare PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

# Add any user requested libraries
target_link_libraries(Gakushu_Bare
    pico_stdlib
    hardware_i2c   # これで hardware/i2c.h が見つかるようになります
    hardware_uart
)

include_directories(
    interface
    driver/sht31
    lib/pico-ssd1306
    lib/pico-ssd1306/frameBuffer
    lib/pico-ssd1306/textRenderer
    lib/pico-ssd1306/shaperenderer # 図形を描くなら必要
)
pico_add_extra_outputs(Gakushu_Bare)

