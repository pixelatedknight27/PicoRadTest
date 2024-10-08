cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(my_project)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
if (TARGET tinyusb_device)
    add_executable(blink
            blink.c
            )

    # pull in common dependencies
    target_link_libraries(blink pico_stdlib)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(blink 1)
    pico_enable_stdio_uart(blink 0)

    # create map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(blink)

    # add url via pico_set_program_url
    # example_auto_set_url(blink)
elseif(PICO_ON_DEVICE)
    message(WARNING "not building hello_usb because TinyUSB submodule is not initialized in the SDK")
endif()
