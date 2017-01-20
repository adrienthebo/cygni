#pragma once

#include <cygni/effects/trunk.hpp>
#include "boundedrand.h"

namespace Cygni {

    struct WillowLeaf {

        WillowLeaf() :
            _hue(0.55, 0.9, 0.0005),
            _lum(0.0, 0.2, 0.0005, 0.0)
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

        BoundedRand<float> _hue;
        BoundedRand<float> _lum;
    };

    struct Willow : public Cygni::Trunk<WillowLeaf> {
        Willow(Output &output) : Cygni::Trunk<WillowLeaf>(output)
        {}
    };
};
