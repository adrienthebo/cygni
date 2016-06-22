#pragma once

#include <cygni/effects/trunk.hpp>
#include "boundedrand.h"

namespace Cygni {

    struct CedarLeaf {

        CedarLeaf() :
            _hue(0.3, 0.7, 0.0005),
            _lum(0.0, 0.05, 0.0005, 0.0)
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

    struct Cedar : public Cygni::Trunk<CedarLeaf> {
        Cedar(Output &output) : Cygni::Trunk<CedarLeaf>(output)
        {}
    };
};
