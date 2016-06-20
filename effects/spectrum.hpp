#pragma once
#include "effect.hpp"
#include <Color.h>

/**
 * Rotate all LEDs through the hue spectrum.
 */
namespace Cygni {
    struct Spectrum : Cygni::Effect {

        Spectrum(Output &output) : Effect(output) {}

        virtual void apply() {
            Color c;

            _hue = next_hue(_hue);
            for(uint32_t idx = 0; idx < _output.size(); idx++) {
                float current_lum = _lum;
                if(_twinkle_probability % random(_twinkle_probability) == 0) {
                    current_lum *= 2;
                }

                float current_sat = _sat;
                if(_unsat_probability % random(_unsat_probability) == 0) {
                    current_sat = 0.0;
                    current_lum /= 2;
                }

                c.convert_hcl_to_rgb(_hue, current_sat, current_lum);
                _output.set_pixel(idx, c.red, c.green, c.blue);
            }
        }

    protected:

        float next_hue(float in) {
            float sum = in + 0.002;
            return sum >= 1.0 ? sum - 1.0 : sum;
        }

        float _hue = 0.0;
        float _sat = 0.8;
        float _lum = 0.05;

        int _twinkle_probability = 10000;
        int _unsat_probability = 25000;
    };
};
