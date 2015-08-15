#include <catch.hpp>

#include <matrix.h>

using Cygni::Matrix;

SCENARIO("matrix: initialization and bounds checking") {
    GIVEN("A matrix of width 0 and height 0") {
        Matrix<int> m(0, 0);

        REQUIRE(m.size() == 0);
        REQUIRE(m.width() == 0);
        REQUIRE(m.height() == 0);

        WHEN("accessing via offset") {
            REQUIRE(m.is_valid_offset(0) == false);
        }

        WHEN("accessing via position") {
            REQUIRE(m.is_valid_position(0, 0) == false);
        }

    }

    GIVEN("A matrix of width 1 and height 1") {
        Matrix<int> m(1, 1);
        REQUIRE(m.size() == 1);
        REQUIRE(m.width() == 1);
        REQUIRE(m.height() == 1);

        WHEN("accessing via offset") {
            REQUIRE(m.is_valid_offset(0) == true);
            REQUIRE(m.is_valid_offset(1) == false);
        }

        WHEN("accessing via position") {
            REQUIRE(m.is_valid_position(0, 0) == true);
            REQUIRE(m.is_valid_position(1, 0) == false);
            REQUIRE(m.is_valid_position(0, 1) == false);
            REQUIRE(m.is_valid_position(1, 1) == false);
        }
    }

    GIVEN("A matrix of width 2 and height 2") {
        Matrix<int> m(2, 2);
        REQUIRE(m.size() == 4);
        REQUIRE(m.width() == 2);
        REQUIRE(m.height() == 2);

        WHEN("accessing via offset") {
            REQUIRE(m.is_valid_offset(0) == true);
            REQUIRE(m.is_valid_offset(3) == true);
            REQUIRE(m.is_valid_offset(4) == false);
        }

        WHEN("accessing via position") {
            REQUIRE(m.is_valid_position(0, 0) == true);
            REQUIRE(m.is_valid_position(0, 1) == true);
            REQUIRE(m.is_valid_position(1, 0) == true);
            REQUIRE(m.is_valid_position(1, 1) == true);

            REQUIRE(m.is_valid_position(0, 2) == false);
            REQUIRE(m.is_valid_position(2, 0) == false);
            REQUIRE(m.is_valid_position(2, 2) == false);
        }
    }
}

SCENARIO("matrix: setting and getting") {
    Matrix<int> m(3, 4);

    GIVEN("setting via offset and accessing via position") {
        m.set(4, 99);
        REQUIRE(*m.get(1, 1) == 99);
    }

    GIVEN("setting via position and accessing via offset") {
        m.set(1, 3, 100);
        REQUIRE(*m.get(10) == 100);
    }
}

SCENARIO("matrix: iterating") {
    WHEN("visiting") {
        Matrix<int> m(3, 4);

        int visited = 0;
        for(auto it : m) {
            ++visited;
        }
        REQUIRE(visited == 12);
    }

    WHEN("altering") {
        Matrix<int> m(3, 4);

        int pos = 0;
        for(auto it : m) {
            m.set(pos, (pos * pos) + 1);
            ++pos;
        }

        REQUIRE(*m.get(0) == 1);
        REQUIRE(*m.get(1, 2) == 50);
        REQUIRE(*m.get(2, 3) == 122);
    }
}
