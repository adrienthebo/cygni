#pragma once
#include <cygni/hcl.hpp>

namespace Cygni {
    struct Hue : HCL {
        Hue() : HCL(0.0, 0.9, 0.05) { }

        void next() {
            clamp_hue_by(_incr);
        }

        // TODO: PICK A NAME FOR THIS SORT OF THING
        inline void step() {
            next();
        }

        void set_incr(float incr) {
            _incr = clamp(incr);
        }

    protected:

        float _incr = 0.01;
    };
};

