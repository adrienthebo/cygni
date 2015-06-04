#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "../grid.h"

using namespace Cygni;

TEST_CASE("Initialize grid", "[grid]") {
    Grid g(5, 10);

    REQUIRE(g.get_width() == 5);
    REQUIRE(g.get_height() == 10);
    REQUIRE(g.get_size() == 50);
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
