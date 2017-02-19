#pragma once
#include "effect.hpp"
#include <cygni/effects/trunk.hpp>

/**
 * Rotate all LEDs through the hue spectrum, with the hue rotation rate proportional to the
 * distance from the edge of the strip.
 */
namespace Cygni {
    struct PeriodicSplit : Cygni::Trunk<Hue> {
        PeriodicSplit(Output &output) : Trunk<Hue>(output) {
            float delta = 0.0002;
            float speed = delta * output.size();
            auto size = output.size();
            for(unsigned int i = 0, half = (output.size() / 2) + 1; i < half; ++i, speed -= delta) {
                nodes[i].set_incr(speed);
                nodes[size - i].set_incr(speed);
            }
        }
    };
};
