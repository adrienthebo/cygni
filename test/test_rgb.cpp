#include <catch.hpp>
#include <rgb.h>

using namespace Cygni;

SCENARIO("Converting to rgb int value") {
    RGB value = {0xF0, 0x7E, 0x0F};
    REQUIRE(value.to_int() == 0xF07E0F);
}

SCENARIO("Fading") {
    RGB value = {0xF0, 0x10, 0x0B};
    RGB expected = {0xE6, 0x06, 0x01};
    value.fade(10);
    REQUIRE(value == expected);
}
