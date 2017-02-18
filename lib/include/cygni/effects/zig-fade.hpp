#pragma once

#include <cygni/effects/zig.hpp>

namespace Cygni {
    struct ZigFade : Zig {

        ZigFade(Output &output) : Zig(output) { }

        void apply() {
            scale();
            Zig::apply();
        }

        void scale() {
            RGB tmp;
            for(uint32_t i = 0; i < _output.size(); i++) {
                tmp.from_int(_output.get_pixel(i));
                tmp.scale(254);
                _output.set_pixel(i, tmp.to_int());
            }
        }
    };
};
