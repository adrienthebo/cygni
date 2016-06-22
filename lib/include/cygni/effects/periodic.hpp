#pragma once
#include "effect.hpp"
#include <cygni/effects/trunk.hpp>

/**
 * Rotate all LEDs through the hue spectrum, with an increasing change rate
 * across the entire strip.
 */
namespace Cygni {

    struct Periodic : Cygni::Trunk<Hue> {

        Periodic(Output &output) : Trunk<Hue>(output) {
            float delta = 0.0002;
            float speed = delta * output.size();
            for(unsigned int i = 0, size = output.size(); i < size; ++i, speed -= delta) {
                nodes[i].set_incr(speed);
            }
        }
    };
};
