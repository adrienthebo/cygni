#pragma once
#include "effect.hpp"
#include <Color.h>
#include <hue.h>

namespace Cygni {
    struct Chase : Cygni::Effect {

        Chase(Output &output) : Effect(output) {}

        void apply() {
            if(++_delay % 5 != 0) {
                return;
            }

            scale();

            uint32_t distance = _output.size() / _count;

            float hue = 0.0;
            for(uint32_t i = 0; i < _count; i++) {
                hue += 1.0 / 6;
                Color c;
                c.convert_hcl_to_rgb(hue, _sat, _lum);

                uint32_t idx = m_index(_counter + (i * distance));
                _output.set_pixel(idx, c.red, c.green, c.blue);
            }
            ++_counter;
        }

        void call(Environment & env) {
            apply();
        }

    private:

        float _sat = 0.9;
        float _lum = 0.05;

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


