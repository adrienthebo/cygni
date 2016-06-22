#pragma once
#include <cygni/hcl.hpp>

namespace Cygni {
    struct Hue : HCL {
        Hue() { }

        void next() {
            _hue += _incr;
        }

        void set_incr(float incr) {
            _incr = clamp(incr);
        }

    private:

        float _incr = 0.01;
    };
};

