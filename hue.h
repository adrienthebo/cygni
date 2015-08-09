#pragma once
#include <Color.h>
#include <rgb.h>

namespace Cygni {
    struct Hue {
        Hue() { }

        Hue(float sat, float lum) {
            _sat = sat;
            _lum = lum;
        }

        void next() {
            _hue += _incr;

            if(_hue >= 1.0) {
                _hue -= 1;
            }

            c.convert_hcl_to_rgb(_hue, _sat, _lum);
        }

        void set_incr(float incr) {
            _incr = incr;
        }

        int red()   { return c.red; }
        int green() { return c.green; }
        int blue()  { return c.blue; }

    private:

        float _hue = 0.0;
        float _sat = 0.9;
        float _lum = 0.05;

        float _incr = 0.01;

        Color c;
    };
};

