# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

cmake_minimum_required(VERSION 3.13)
# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(tamarin_c)
 
pico_sdk_init()

add_executable(tamarin_c)

pico_generate_pio_header(tamarin_c ${CMAKE_CURRENT_LIST_DIR}/probe.pio)
pico_generate_pio_header(tamarin_c ${CMAKE_CURRENT_LIST_DIR}/uart_rx.pio)

target_sources(tamarin_c PRIVATE
        main.c
        tcpm_driver.c
        tamarin_hw.c
        FUSB302.c
        usb_pd.c
        tamarin_probe.c
        usb_descriptors.c)
# Required so the build finds tusb_config.h
target_include_directories(tamarin_c PRIVATE ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(tamarin_c PRIVATE
        pico_stdlib
        pico_bootrom
        tinyusb_device
        tinyusb_board
        hardware_pio
        hardware_i2c
        hardware_uart
        )

pico_add_extra_outputs(tamarin_c)



# enable usb output, disable uart output
# pico_enable_stdio_usb(tamarin_c 1)
pico_enable_stdio_uart(tamarin_c 0)
