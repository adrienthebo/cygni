#pragma once

#include <cygni/effects/trunk.hpp>
#include <cygni/util/boundedrand.hpp>

namespace Cygni {

    struct CedarLeaf {

        CedarLeaf() :
            _hue(0.3, 0.7, 0.0005),
            _lum(0.0, 0.05 * BRIGHTNESS_FACTOR, 0.0005, 0.0)
        {}

        void step() {
            _hue.step();
            _lum.step();
        }

        uint32_t to_int() const {
            HCL hcl { _hue.val, 0.9, _lum.val };
            return hcl.to_int();
        }

    private:
        Cygni::Util::BoundedRand<float> _hue;
        Cygni::Util::BoundedRand<float> _lum;
    };

    struct Cedar : public Cygni::Trunk<CedarLeaf> {
        Cedar(Output &output) : Cygni::Trunk<CedarLeaf>(output)
        {}
    };
};
