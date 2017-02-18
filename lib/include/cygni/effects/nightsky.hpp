#pragma once

#include <cygni/effects/trunk.hpp>
#include <cygni/util/boundedrand.hpp>

namespace Cygni {

    struct Star {

        Star() :
            _lum(0.0, 0.05 * BRIGHTNESS_FACTOR, 0.001, 0.0)
        {}

        void step() {
            _lum.step();
        }

        uint32_t to_int() const {
            HCL hcl { 0.0, 0.0, _lum.val };
            return hcl.to_int();
        }

    private:
        Cygni::Util::BoundedRand<float> _lum;
    };

    struct NightSky : public Cygni::Trunk<Star> {
        NightSky(Output &output) : Cygni::Trunk<Star>(output)
        {}
    };
};

