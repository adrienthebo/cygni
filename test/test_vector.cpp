#include <catch.hpp>

#include <vector.h>

using Cygni::Vector;

SCENARIO("vector: initialization and bounds checking") {
    GIVEN("A vector of length 0") {
        Vector<int> v(0);
        REQUIRE(v.size() == 0);
        REQUIRE(v.is_valid_offset(0) == false);
    }

    GIVEN("A vector of length 1") {
        Vector<int> v(1);
        REQUIRE(v.size() == 1);
        REQUIRE(v.is_valid_offset(0) == true);
        REQUIRE(v.is_valid_offset(1) == false);
    }
}

SCENARIO("vector: setting and getting") {
    Vector<int> v(1);

    GIVEN("A valid offset") {
        v.set(0, 99);
        REQUIRE(*v.get(0) == 99);
    }

    GIVEN("An invalid offset") {
        v.set(1, -1);
        REQUIRE(v.get(1) == nullptr);
    }
}

SCENARIO("vector: iterating") {
    WHEN("visiting") {
        Vector<int> v(3);

        int visited = 0;
        for(auto it : v) {
            ++visited;
        }
        REQUIRE(visited == 3);
    }

    WHEN("altering") {
        Vector<int> v(3);

        int pos = 0;
        for(auto it : v) {
            v.set(pos, (pos * pos) + 1);
            ++pos;
        }

        REQUIRE(*v.get(0) == 1);
        REQUIRE(*v.get(1) == 2);
        REQUIRE(*v.get(2) == 5);
    }
}
