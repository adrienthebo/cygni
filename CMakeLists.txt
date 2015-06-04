cmake_minimum_required (VERSION 3.0)
project (Cygni)
add_executable(main main.cpp)

include_directories(vendor/Catch/include)

add_library(cygni grid.cpp)

add_subdirectory(test)

enable_testing()

add_test(NAME "cygni\\ unit\\ tests" COMMAND test/test_cygni)
