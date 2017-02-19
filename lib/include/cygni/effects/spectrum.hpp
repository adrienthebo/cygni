#pragma once
#include "effect.hpp"

/**
 * Rotate all LEDs through the hue spectrum.
 */
namespace Cygni {
    struct Spectrum : Cygni::Effect {

        Spectrum(Output &output) : Effect(output), _hcl(0.0, 0.9, 0.05) {
        }

        virtual void apply() {
            _hcl.clamp_hue_by(0.002);
            for(uint32_t idx = 0; idx < _output.size(); idx++) {
                HCL tmp(_hcl);

                if(_twinkle_probability % random(_twinkle_probability) == 0) {
                    tmp.clamp_lum(tmp.lum() * random(4));
                }

                _output.set_pixel(idx, tmp.to_int());
            }
        }

        void call(Environment & env) { apply(); }
    protected:
        HCL _hcl;

        static constexpr int _twinkle_probability = 2500;
    };
};
