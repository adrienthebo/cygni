#include <catch.hpp>
#include <rgb.h>

using namespace Cygni;

SCENARIO("Converting from RGB int value") {
    RGB value;
    RGB expected = {0xFE, 0x56, 0x1A};
    value.from_int(0xFE561A);
    REQUIRE(value == expected);
}

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

SCENARIO("Scaling") {
    RGB value = {0xFF, 0xF0, 0x0F};
    RGB expected = {0x7F, 0x78, 0x07};
    value.scale(128);
    REQUIRE(value == expected);
}
