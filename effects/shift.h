#pragma once
#include "effect.h"
#include <Color.h>

namespace Cygni {
    struct Shift : Cygni::Effect {

        Shift(Output &output) : Effect(output) {}

        virtual void apply() {
            Color c;
            float current_hue = _hue;
            for(uint32_t idx = 0; idx < _output.size(); idx++) {
                current_hue = next_hue(current_hue);

                float current_lum = _lum;
                if(_twinkle_probability % random(_twinkle_probability) == 0) {
                    current_lum *= 2;
                }

                float current_sat = _sat;
                if(_unsat_probability % random(_unsat_probability) == 0) {
                    current_sat = 0.0;
                    current_lum = 0.5;
                }

                c.convert_hcl_to_rgb(current_hue, current_sat, current_lum);
                _output.set_pixel(idx, c.red, c.green, c.blue);
            }
            _hue = next_hue(_hue);
        }

    protected:



        float next_hue(float in) {
            float sum = in + 0.02;
            return sum >= 1.0 ? sum - 1.0 : sum;
        }

        float _hue = 0.0;
        float _sat = 0.8;
        float _lum = 0.05;

        int _twinkle_probability = 5000;
        int _unsat_probability = 5000;
    };
};
