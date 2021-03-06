#pragma once
#include "effect.hpp"
#include <cygni/hue.hpp>

namespace Cygni {
    struct Spin : Cygni::Effect {

        Spin(Output &output) : Effect(output) {

            _h.set_incr(0.001);
        }

        void apply() {
            uint32_t idx = ++_counter % _output.size();

            _output.set_pixel(idx, _h.to_int());

            if(_counter % 2 == 0) {
                scale();
            }
            _h.step();
        }

        void call(Environment & env) { apply(); }
    private:

        uint32_t _counter = 0;
        Hue _h;

        void scale() {
            RGB tmp;
            for(uint32_t i = 0; i < _output.size(); i++) {
                tmp.from_int(_output.get_pixel(i));
                tmp.scale(240);
                _output.set_pixel(i, tmp.to_int());
            }
        }
    };
};

