#pragma once
#include <cygni/hcl.hpp>

namespace Cygni {
    struct Hue : HCL {
        Hue() : HCL(0.0, 0.9, 0.05) { }

        Hue(const Hue & rhs) : HCL(rhs) {
            _incr = rhs._incr;
        }

        void step() {
            clamp_hue_by(_incr);
        }

        void set_incr(float incr) {
            _incr = clamp(incr);
        }

    protected:

        float _incr = 0.01;
    };
};

