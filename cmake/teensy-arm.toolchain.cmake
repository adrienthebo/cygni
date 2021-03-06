# teensy-arm.toolchain.cmake

################################################################################
# Arduino configuration

set(ARDUINO_ROOT "/usr/share/arduino")
set(ARDUINO_VERSION "161" CACHE STRING "Version of the Arduino SDK")
add_definitions("-DARDUINO=${ARDUINO_VERSION}")

################################################################################
# ARM toolchain

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_CROSSCOMPILING 1)

set(TRIPLE "arm-none-eabi")

set(TOOLCHAIN_ROOT "${ARDUINO_ROOT}/hardware/tools/arm")
set(TOOLCHAIN_BIN_PREFIX "${TOOLCHAIN_ROOT}/bin/${TRIPLE}")

set(CMAKE_C_COMPILER   "${TOOLCHAIN_BIN_PREFIX}-gcc" CACHE PATH "gcc" FORCE)
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_BIN_PREFIX}-g++" CACHE PATH "g++" FORCE)
set(CMAKE_AR           "${TOOLCHAIN_BIN_PREFIX}-ar" CACHE PATH "archive" FORCE)
set(CMAKE_LINKER       "${TOOLCHAIN_BIN_PREFIX}-ld" CACHE PATH "linker" FORCE)
set(CMAKE_NM           "${TOOLCHAIN_BIN_PREFIX}-nm" CACHE PATH "nm" FORCE)
set(CMAKE_OBJCOPY      "${TOOLCHAIN_BIN_PREFIX}-objcopy" CACHE PATH "objcopy" FORCE)
set(CMAKE_OBJDUMP      "${TOOLCHAIN_BIN_PREFIX}-objdump" CACHE PATH "objdump" FORCE)
set(CMAKE_STRIP        "${TOOLCHAIN_BIN_PREFIX}-strip" CACHE PATH "strip" FORCE)
set(CMAKE_RANLIB       "${TOOLCHAIN_BIN_PREFIX}-ranlib" CACHE PATH "ranlib" FORCE)

################################################################################
# Teensy library configuration configuration

set(TEENSY_CORES_ROOT "${ARDUINO_ROOT}/hardware/teensy/avr/cores" CACHE PATH "Path to the Teensy 'cores' repository")

set(TEENSY_ROOT "${TEENSY_CORES_ROOT}/teensy3")

set(TEENSYDUINO_VERSION "121" CACHE STRING "Version of the Teensyduino SDK")
add_definitions("-DTEENSYDUINO=${TEENSYDUINO_VERSION}")

################################################################################
# Teensy hardware configuration

set(TEENSY_MODEL "MK20DX256")

set(TEENSY_FREQUENCY "96" CACHE STRING "Frequency of the Teensy MCU (Mhz)")
set_property(CACHE TEENSY_FREQUENCY PROPERTY STRINGS 96 72 48 24 16 8 4 2)

set(TEENSY_USB_MODE "SERIAL" CACHE STRING "What kind of USB device the Teensy should emulate")
set_property(CACHE TEENSY_USB_MODE PROPERTY STRINGS SERIAL HID SERIAL_HID MIDI RAWHID FLIGHTSIM)

add_definitions("-D__${TEENSY_MODEL}__")
add_definitions("-DF_CPU=${TEENSY_FREQUENCY}000000")

# Hardcoded for sanity, might not be good for the long term.
add_definitions("-DUSB_${TEENSY_USB_MODE}")

################################################################################
# Teensy library flags

include_directories(${TEENSY_ROOT})

################################################################################
# Teensy compiler/linker flags

set(ARCH_FLAGS "-mcpu=cortex-m4 -mthumb")

set(CMAKE_C_FLAGS "-Os -Wall -nostdlib -ffunction-sections -fdata-sections -MMD ${ARCH_FLAGS}" CACHE STRING "c flags")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -fno-exceptions -fno-rtti -felide-constructors -std=gnu++0x" CACHE STRING "c++ flags")

set(LINKER_FLAGS "-Os -Wl,--gc-sections,--defsym=__rtc_localtime=0 --specs=nano.specs ${ARCH_FLAGS} -T${TEENSY_ROOT}/mk20dx256.ld" )
set(LINKER_LIBS "-larm_cortexM4l_math -lm" )
set(CMAKE_SHARED_LINKER_FLAGS "${LINKER_FLAGS}" CACHE STRING "linker flags" FORCE)
set(CMAKE_MODULE_LINKER_FLAGS "${LINKER_FLAGS}" CACHE STRING "linker flags" FORCE)
set(CMAKE_EXE_LINKER_FLAGS "${LINKER_FLAGS}" CACHE STRING "linker flags" FORCE)

# Do not pass flags like '-ffunction-sections -fdata-sections' to the linker.
# This causes undefined symbol errors when linking.
set(CMAKE_CXX_LINK_EXECUTABLE "<CMAKE_C_COMPILER> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> -o <TARGET>  <OBJECTS> <LINK_LIBRARIES> ${LINKER_LIBS}" CACHE STRING "Linker command line" FORCE)

add_definitions(-DLAYOUT_US_ENGLISH)
add_definitions(-DUSB_VID=null)
add_definitions(-DUSB_PID=null)
