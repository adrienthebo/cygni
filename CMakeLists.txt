cmake_minimum_required(VERSION 3.0)
project(Cygni)

add_library(cygni grid.cpp)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_subdirectory(test)
else()
  include("vendor/teensy-cmake/cmake/Teensy.cmake")

  include_directories(vendor/OctoWS2811)
  include_directories(.)
  add_teensy_library(OctoWS2811 vendor/OctoWS2811/OctoWS2811.cpp)

  add_teensy_core(teensy_core)

  add_teensy_executable(main exe/main.cpp grid.cpp)
  target_link_libraries(main OctoWS2811 teensy_core)

  add_teensy_executable(blink exe/blink.cpp)
  target_link_libraries(blink teensy_core)
endif()
