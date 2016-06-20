#pragma once

#include <cygni/effects/trunk.hpp>
#include "boundedrand.h"

namespace Cygni {

    struct Star {

        Star() :
            _lum(0.0, 0.05, 0.001, 0.0)
        {}

        void step() {
            _lum.step();
        }

        float hue() {
           return 0.0;
        } 

        float sat() {
            return 0.0;
        }

        float lum() {
            return _lum.val;
        }

    private:

        BoundedRand<float> _lum;
    };

    struct NightSky : public Cygni::Trunk<Star> {
        NightSky(Output &output) : Cygni::Trunk<Star>(output)
        {}
    };
};

