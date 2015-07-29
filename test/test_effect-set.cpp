#include <catch.hpp>
#include "effect-set.h"

using namespace Cygni;

struct DummyEffect : Effect {
    void apply(Cygni::Driver *driver) { applied = true; }
    bool applied = false;
};

struct DummyDriver : Driver {
    void apply() {};
}

SCENARIO("Initialize effect set") {
    EffectSet es(1);
    REQUIRE(es.get_size() == 1);
}

SCENARIO("Incrementing the effect index") {
    DummyEffect d0, d1;
    Effect *effects[] = {&d0, &d1};

    EffectSet es(2, effects);

    WHEN("index has not been altered") {
        REQUIRE(es.get_index() == 0);
        REQUIRE(es.current() == &d0);
    }

    es.next_effect();

    WHEN("index has been incremented") {
        REQUIRE(es.get_index() == 1);
        REQUIRE(es.current() == &d1);
    }

    es.next_effect();

    WHEN("index rolls over") {
        REQUIRE(es.current() == &d0);
        REQUIRE(es.get_index() == 0);
    }
}

SCENARIO("Forwarding an apply") {
    DummyEffect d0;
    Effect *effects[] = {&d0};

    EffectSet es(1, effects);
    es.apply();
    REQUIRE(d0.applied);

}
