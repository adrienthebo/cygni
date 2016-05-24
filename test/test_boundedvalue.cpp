#include <catch.hpp>
#include "../boundedvalue.h"

using namespace Cygni;

SCENARIO("bounded value", "[BoundedValue]") {
    BoundedValue<float> f { 0.0, 0.5, 0.1, 0.2 };

    GIVEN("initialization") {
        REQUIRE(f.min == 0.0f);
        REQUIRE(f.max == 0.5f);
        REQUIRE(f.by == 0.1f);
        REQUIRE(f.val == 0.2f);
    }

    GIVEN("Basic step") {
        REQUIRE(f.step() == 0.3f);
        REQUIRE(f.val == 0.3f);
    }

    GIVEN("Hitting max") {
        f.val = 0.5f;
        REQUIRE(f.step() == 0.4f);
    }

    GIVEN("Hitting min") {
        f.val = 0.0f;
        REQUIRE(f.step() == 0.1f);
    }
}
