#pragma once
#include "effect.hpp"
#include <cygni/hue.hpp>

/**
 * Rotate over the hue spectrum over a length of LEDs, creating
 * a rippling color effect.
 */
namespace Cygni {
    struct Shift : Cygni::Effect {

        Shift(Output &output) : Effect(output) {
            _hue.clamp_chroma(0.8);
            _hue.set_incr(0.003);
        }

        virtual void apply() {
            Hue current(_hue);
            current.set_incr(0.02);
            for(uint32_t idx = 0; idx < _output.size(); idx++) {
                Hue glittered(current);
                if(_twinkle_probability % random(_twinkle_probability) == 0) {
                    glittered.clamp_lum(current.lum() * 2);
                }

                if(_unsat_probability % random(_unsat_probability) == 0) {
                    glittered.clamp_chroma(0.0);
                    glittered.clamp_chroma(current.chroma() / 2);
                }

                _output.set_pixel(idx, glittered.to_int());
                current.next();
            }
            _hue.next();
        }

        void call(Environment & env) { apply(); }
    protected:

        Hue _hue;

        int _twinkle_probability = 100000;
        int _unsat_probability = 25000;
    };
};
