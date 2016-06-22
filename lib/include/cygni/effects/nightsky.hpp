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

        uint32_t to_int() const {
            HCL hcl { 0.0, 0.0, _lum.val };
            return hcl.to_int();
        }

    private:

        BoundedRand<float> _lum;
    };

    struct NightSky : public Cygni::Trunk<Star> {
        NightSky(Output &output) : Cygni::Trunk<Star>(output)
        {}
    };
};
