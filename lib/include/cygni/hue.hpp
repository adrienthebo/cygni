#pragma once
#include <cygni/hcl.hpp>

namespace Cygni {
    struct Hue : HCL {
        Hue() : HCL(0.0, 0.9, 0.05) { }

        void next() {
            _hue += _incr;
        }

        void set_incr(float incr) {
            _incr = clamp(incr);
        }

    protected:

        float _incr = 0.01;
    };
};

