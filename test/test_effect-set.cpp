#include <catch.hpp>
#include "effect-set.h"

using namespace Cygni;

SCENARIO("Initialize effect set") {
    EffectSet es(1);
    REQUIRE(es.get_size() == 1);
}
