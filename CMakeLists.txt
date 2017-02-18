cmake_minimum_required(VERSION 3.0)
project(Cygni)

include_directories(.)
include_directories("lib/include")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_library(cygni lib/src/rgb.cpp lib/src/hcl.cpp grid.cpp)
  target_compile_features(cygni PUBLIC cxx_nonstatic_member_init cxx_range_for)

  add_subdirectory(test)
else()
  include("vendor/teensy-cmake/cmake/Teensy.cmake")


  include_directories(vendor/Color)
  include_directories(vendor/OctoWS2811)
  include_directories(vendor/Bounce2)

  add_teensy_library(OctoWS2811 vendor/OctoWS2811/OctoWS2811.cpp)
  add_teensy_library(Color vendor/Color/Color.cpp)
  add_teensy_library(Bounce2 vendor/Bounce2/Bounce2.cpp)

  add_teensy_core(teensy_core)

  add_teensy_library(cygni grid.cpp lib/src/rgb.cpp lib/src/hcl.cpp drivers/octo-driver.cpp)

  add_teensy_executable(burn-in exe/burn-in.cpp grid.cpp)
  target_link_libraries(burn-in cygni OctoWS2811 teensy_core)

  add_teensy_executable(blink exe/blink.cpp)
  target_link_libraries(blink teensy_core)

  add_teensy_executable(octo-pin-pulse exe/octo-pin-pulse.cpp)
  target_link_libraries(octo-pin-pulse teensy_core)

  add_teensy_executable(octo-pin-steady exe/octo-pin-steady.cpp)
  target_link_libraries(octo-pin-steady teensy_core)

  add_teensy_executable(huron exe/huron.cpp grid.cpp vendor/OctoWS2811/OctoWS2811.cpp)
  target_link_libraries(huron Color Bounce2 cygni OctoWS2811 teensy_core)

endif()
