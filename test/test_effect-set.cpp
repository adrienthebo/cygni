#include <catch.hpp>

#include <effects/effect.h>
#include <outputs/output.h>
#include <drivers/driver.h>

#include "effect-set.h"

using namespace Cygni;

struct DummyOutput : Output {
    DummyOutput() { }
    void set_pixel(int idx, int r, int g, int b) { };
    void set_pixel(int idx, int rgb) { };

    uint32_t get_pixel(uint32_t idx) { return 0; }

    uint32_t size() { return 0; }
    uint32_t width() { return 0; }
    uint32_t height() { return 0; }
};

struct DummyEffect : Effect {
    DummyEffect(Output &o) : Effect(o) {}

    void apply() { applied = true; }
    bool applied = false;
};

SCENARIO("Initialize effect set") {
    EffectSet es(1);
    REQUIRE(es.get_size() == 1);
}

SCENARIO("Incrementing the effect index") {
    DummyOutput o;

    DummyEffect d0(o);
    DummyEffect d1(o);

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
