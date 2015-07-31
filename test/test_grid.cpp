#include <catch.hpp>
#include "../grid.h"
#include "../rgb.h"

using namespace Cygni;

TEST_CASE("Initialize grid", "[grid]") {
    Grid g(5, 10);

    REQUIRE(g.get_width() == 5);
    REQUIRE(g.get_height() == 10);
    REQUIRE(g.get_size() == 50);
}

TEST_CASE("Initialize grid - zero out memory", "[grid]") {
    Grid g(2, 3);

    RGB val;
    RGB blank = {0, 0, 0};

    for(int x = 0; x < g.get_width(); x++) {
        for(int y = 0; y < g.get_height(); y++) {
            val = *g.get_pixel(x, y);
            REQUIRE(val == blank);
        }
    }
}

TEST_CASE("Bounds check - x axis", "[grid]") {
    Grid g(5, 10);

    REQUIRE(g.is_valid_x_index(-1) == false);
    REQUIRE(g.is_valid_x_index(0) == true);
    REQUIRE(g.is_valid_x_index(5) == false);
}

TEST_CASE("Bounds check - y axis", "[grid]") {
    Grid g(5, 10);

    REQUIRE(g.is_valid_y_index(-1) == false);
    REQUIRE(g.is_valid_y_index(0) == true);
    REQUIRE(g.is_valid_y_index(10) == false);
}

TEST_CASE("Bounds check - position", "[grid]") {
    Grid g(5, 10);

    REQUIRE(g.is_valid_position(-1, 0) == false);
    REQUIRE(g.is_valid_position(0, -1) == false);
    REQUIRE(g.is_valid_position(0, 0) == true);
    REQUIRE(g.is_valid_position(5, 0) == false);
    REQUIRE(g.is_valid_position(0, 10) == false);
}

TEST_CASE("Bounds check - offset", "[grid]") {
    Grid g(2, 2);

    REQUIRE(g.is_valid_offset(0) == true);
    REQUIRE(g.is_valid_offset(3) == true);
    REQUIRE(g.is_valid_offset(4) == false);
    REQUIRE(g.is_valid_offset(-1) == false);
}

TEST_CASE("Assignment and retrieval", "[grid]") {
    Grid g(3, 3);
    RGB val = {10, 25, 3};
    RGB expected = {10, 25, 3};

    g.set_pixel(1, 2, &val);
    RGB ret = *g.get_pixel(1, 2);

    REQUIRE(ret == expected);

    RGB blank_val = {0, 0, 0};

    // Assert that no other values have been changed
    for(int x = 0; x < g.get_width(); x++) {
        for(int y = 0; y < g.get_height(); y++) {
            if(x == 1 && y == 2) {
                continue;
            }
            REQUIRE(*g.get_pixel(x, y) == blank_val);
        }
    }
}

TEST_CASE("Offset retrieval") {
    Grid g(3, 3);
    RGB val = {128, 64, 32};
    RGB expected = {128, 64, 32};
    g.set_pixel(1, 2, &val);

    RGB ret = *g.get_pixel(1, 2);
    REQUIRE(ret == expected);
}

TEST_CASE("Invalid assignment", "[grid]") {
    Grid g(5, 10);
    RGB val = {10, 25, 3};

    g.set_pixel(10, 20, &val);

    RGB *ret = g.get_pixel(10, 20);

    REQUIRE(ret == 0);
}

TEST_CASE("range based for loop - visit all locations") {
    Grid g(3, 3);

    int visited = 0;
    for(auto it : g) {
        ++visited;
    }
    REQUIRE(visited == 9);
}

TEST_CASE("range based for loop - alter all locations") {
    Grid g(3, 3);

    int count = 0;
    for(auto& it : g) {
        it.red = count;
        it.green = count;
        it.blue = count;
        ++count;
    }

    for(int y = 0; y < g.get_height(); y++) {
        for(int x = 0; x < g.get_width(); x++) {
            int level = x + y * 3;

            RGB expected = {level, level, level};
            RGB ret = *g.get_pixel(x,  y);

            REQUIRE(ret == expected);
        }
    }
}
