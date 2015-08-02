#pragma once
#include <driver.h>
#include "effect.h"
#include <Color.h>

namespace Cygni {
    struct Shift : Cygni::Effect {

        Shift() {}

        Shift(float sat, float lum) {
            _sat = sat;
            _lum = lum;
        }

        virtual void apply(Cygni::Driver *driver) {
            Color c;
            float current_hue = _hue;
            for(int idx = 0; idx < driver->get_length(); idx++) {
                current_hue += 0.02;

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
                driver->set_pixel(idx, c.red, c.green, c.blue);
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

        int _twinkle_probability = 1000;
        int _unsat_probability = 5000;
    };
};
