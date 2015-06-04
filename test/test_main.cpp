#define CATCH_CONFIG_MAIN
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

    RGB *val;

    for(int x = 0; x < g.get_width(); x++) {
        for(int y = 0; y < g.get_height(); y++) {
            val = g.get_pixel(x, y);
            REQUIRE(val->red == 0);
            REQUIRE(val->green == 0);
            REQUIRE(val->blue == 0);
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

TEST_CASE("Assignment and retrieval", "[grid]") {
    Grid g(5, 10);
    RGB val = {10, 25, 3};

    g.set_pixel(1, 2, &val);

    RGB ret = *g.get_pixel(1, 2);

    REQUIRE(ret.red == 10);
    REQUIRE(ret.green == 25);
    REQUIRE(ret.blue == 3);

    RGB *null_val;

    // Assert that no other values have been changed
    for(int x = 0; x < g.get_width(); x++) {
        for(int y = 0; y < g.get_height(); y++) {
            if(x == 1 && y == 2) {
                continue;
            }
            null_val = g.get_pixel(x, y);
            REQUIRE(null_val->red == 0);
            REQUIRE(null_val->green == 0);
            REQUIRE(null_val->blue == 0);
        }
    }
}

TEST_CASE("Invalid assignment", "[grid]") {
    Grid g(5, 10);
    RGB val = {10, 25, 3};

    g.set_pixel(10, 20, &val);

    RGB *ret = g.get_pixel(10, 20);

    REQUIRE(ret == 0);
}
