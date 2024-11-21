cmake_minimum_required(VERSION 3.13)

set(CXX /usr/bin/g++)
set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS OFF)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.0.0)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico2 CACHE STRING "Board type")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -flto=auto -fno-rtti -fno-exceptions -ffunction-sections -fdata-sections -fomit-frame-pointer -DNDEBUG -s ")

include(pico_sdk_import.cmake)
project(alarmclock-cpp C CXX ASM)
set(PICO_CXX_ENABLE_EXCEPTIONS 1)
pico_sdk_init()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/target)
file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(alarmclock-cpp ${SOURCES})

pico_set_program_name(alarmclock-cpp "alarmclock-cpp")
pico_set_program_version(alarmclock-cpp "0.1")
pico_enable_stdio_uart(alarmclock-cpp 0)
pico_enable_stdio_usb(alarmclock-cpp 1)

target_include_directories(alarmclock-cpp PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
)
target_link_libraries(alarmclock-cpp 
    pico_stdlib 
    pico_multicore
    hardware_pwm
    hardware_timer
    hardware_watchdog
    hardware_clocks
)


pico_add_extra_outputs(alarmclock-cpp)

# Custom command to copy UF2 file to /target folder
add_custom_command(TARGET alarmclock-cpp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/../alarmclock-cpp.uf2 ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/
    COMMAND ${CMAKE_COMMAND} -E rm ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/../alarmclock-cpp.uf2
    DEPENDS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/../alarmclock-cpp.uf2
)
