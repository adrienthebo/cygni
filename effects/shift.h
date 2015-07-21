#pragma once
#include <driver.h>
#include <Color.h>

namespace Cygni {
    struct Shift : Cygni::Effect {

        virtual void apply(Cygni::OctoDriver *driver) {
            Color c;
            float current_hue = _hue;
            for(int idx = 0; idx < driver->get_length(); idx++) {
                current_hue += 0.02;
                c.convert_hcl_to_rgb(current_hue, _sat, _lum);
                driver->set_pixel(idx, c.red, c.green, c.blue);
            }
            _hue = next_hue(_hue);
        }

        private:

        float next_hue(float in) {
            float sum = in + 0.01;
            return sum >= 1.0 ? sum - 1.0 : sum;
        }

        float _hue = 0.0;
        float _sat = 0.8;
        float _lum = 0.05;
    };
};
