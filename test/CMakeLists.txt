include_directories(../vendor/Catch/include)

add_executable(test_cygni test_main.cpp test_grid.cpp test_effect-set.cpp
    test_rgb.cpp)
target_link_libraries(test_cygni cygni)

enable_testing()
add_test(NAME "cygni unit tests" COMMAND test/test_cygni)
