#pragma once
#include "effect.hpp"
#include <cygni/effects/trunk.hpp>
#include <cygni/hue.hpp>

/**
 * Rotate over the hue spectrum over a length of LEDs, creating
 * a rippling color effect.
 */
namespace Cygni {
    struct Shift : Cygni::Trunk<Hue> {

        Shift(Output &output) : Trunk<Hue>(output) {
            float hue_offset = 0.0;
            float step = 0.02;
            for(unsigned int i = 0, size = output.size(); i < size; ++i, hue_offset += step) {
                Hue & curr = nodes[i];
                curr.clamp_chroma(0.8);
                curr.clamp_hue_by(hue_offset);
                curr.set_incr(0.003);
            }
        }

        virtual void apply() {
            Trunk<Hue>::apply();

            for(uint32_t idx = 0, size = _output.size(); idx < size; idx++) {
                Hue glittered(nodes[idx]);

                if(_twinkle_probability % random(_twinkle_probability) == 0) {
                    glittered.clamp_lum(glittered.lum() * 3);
                }

                if(_unsat_probability % random(_unsat_probability) == 0) {
                    glittered.clamp_chroma(0.0);
                    glittered.clamp_chroma(glittered.chroma() / 2);
                }

                _output.set_pixel(idx, glittered.to_int());
            }
        }

        void call(Environment & env) { apply(); }
    protected:

        Hue _hue;

        int _twinkle_probability = 100000;
        int _unsat_probability = 25000;
    };
};
