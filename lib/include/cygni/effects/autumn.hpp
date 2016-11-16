#pragma once

#include <cygni/effects/trunk.hpp>
#include "boundedrand.h"

namespace Cygni {

    struct AutumnLeaf {

        AutumnLeaf() :
            _hue(0.0, 0.1, 0.0005),
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

    struct Autumn : public Cygni::Trunk<AutumnLeaf> {
        Autumn(Output &output) : Cygni::Trunk<AutumnLeaf>(output)
        {}
    };
};
