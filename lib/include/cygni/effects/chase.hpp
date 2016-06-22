#pragma once
#include "effect.hpp"
#include <cygni/hue.hpp>

namespace Cygni {
    /**
     * Six colors spread out across the hue spectrum, one chasing after
     * another.
     *
     * This pattern is pretty ugly, especially because it doesn't do fuckall
     * in dithering. It's jerky and harsh.
     */
    struct Chase : Cygni::Effect {

        Chase(Output &output) : Effect(output) {}

        void apply() {
            if(++_delay % 5 != 0) {
                return;
            }

            scale();

            uint32_t distance = _output.size() / _count;

            HCL hcl { 0.0, 0.9, 0.05 };

            for(uint32_t i = 0; i < _count; i++) {
                hcl.clamp_hue_by(1.0 / 6.0);
                uint32_t idx = m_index(_counter + (i * distance));
                _output.set_pixel(idx, hcl.to_int());
            }
            ++_counter;
        }

        void call(Environment & env) {
            apply();
        }

    private:

        uint32_t _count = 6;

        uint32_t m_index(uint32_t in) {
            return in % _output.size();
        }

        uint32_t _counter = 0;
        uint32_t _delay = 0;

        void scale() {
            RGB tmp;
            for(uint32_t i = 0; i < _output.size(); i++) {
                tmp.from_int(_output.get_pixel(i));
                tmp.scale(192);
                _output.set_pixel(i, tmp.to_int());
            }
        }
    };
};


