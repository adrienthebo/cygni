#pragma once
#include <Color.h>
#include <rgb.h>

namespace Cygni {
    struct Hue {
        Hue() {
            _sat = 0.9;
            _lum = 0.02;
        }

        Hue(float sat, float lum) {
            _sat = sat;
            _lum = lum;
        }

        void next() {
            _hue += 0.01;

            if(_hue >= 1.0) {
                _hue -= 1;
            }

            c.convert_hcl_to_rgb(_hue, _sat, _lum);
        }

        int red()   { return c.red; }
        int green() { return c.green; }
        int blue()  { return c.blue; }

    private:

        float _hue = 0.0;
        float _sat;
        float _lum;
        Color c;
    };
};

