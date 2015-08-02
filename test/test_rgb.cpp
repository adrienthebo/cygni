#include <catch.hpp>
#include <rgb.h>

using namespace Cygni;

SCENARIO("Converting to rgb int value") {
    RGB value = {0xF0, 0x7E, 0x0F};
    REQUIRE(value.to_int() == 0xF07E0F);
}
