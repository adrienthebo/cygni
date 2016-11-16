#include <catch.hpp>

#include <cygni/effects/effect.hpp>
#include <outputs/output.h>
#include <drivers/driver.h>

#include <cygni/effect-set.hpp>

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
    void call(Environment & env) { apply(); }
    bool applied = false;
};

SCENARIO("Initialize effect set") {
    EffectSet es(1);
    REQUIRE(es.get_size() == 1);
}

SCENARIO("Changing the effect index") {
    DummyOutput o;

    DummyEffect d0(o);
    DummyEffect d1(o);

    Effect *effects[] = {&d0, &d1};


    WHEN("index is at initial state") {
        EffectSet subject(2, effects);
        REQUIRE(subject.get_index() == 0);
        REQUIRE(subject.current() == &d0);
    }


    WHEN("incrementing the index") {
        EffectSet subject(2, effects);
        WHEN("not overflowing") {
            subject.next_effect();

            REQUIRE(subject.get_index() == 1);
            REQUIRE(subject.current() == &d1);
        }

        WHEN("overflowing") {
            subject.next_effect();

            REQUIRE(subject.current() == &d0);
            REQUIRE(subject.get_index() == 0);
        }
    }

    WHEN("decrementing the index") {
        EffectSet subject(2, effects);
        WHEN("not underflowing") {
            subject.next_effect();
            subject.prev_effect();

            REQUIRE(subject.get_index() == 0);
            REQUIRE(subject.current() == &d0);
        }

        WHEN("underflowing") {
            subject.prev_effect();
            subject.prev_effect();

            REQUIRE(subject.current() == &d1);
            REQUIRE(subject.get_index() == 1);
        }
    }
}
