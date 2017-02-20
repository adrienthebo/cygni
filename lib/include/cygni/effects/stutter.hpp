#pragma once
#include "effect.hpp"
#include <grid.h>
#include <cygni/hcl.hpp>
#include <cygni/util.hpp>

using namespace Cygni::Util;

namespace Cygni {

    struct Stutter : Effect {

        static const uint8_t _indices_size = 10;
        uint32_t _indices[_indices_size];

        Stutter(Output &output) : Effect(output) {
            set_indices();
            set_color();
            cycle();
        }

        void apply() {
            if(--_indices_duration <= 0) {
                /* We're selecting a new set of indices. Reduce the brightness
                 * of the currently selected indices to reduce power
                 * consumption and offset the brightness of the next indices,
                 * and boost the saturation of the current indices to reduce
                 * the low sat Easter effect.
                 */
                HCL dimming_hcl(_hcl);
                dimming_hcl.clamp_chroma_by(0.15);
                dimming_hcl.clamp_lum(_hcl.lum() * 0.15);
                wipe_indices(dimming_hcl);
                set_indices();
                set_color();
            }

            if(--_cycle_duration > 0) {
                return;
            }

            cycle();
            wipe_indices(_hcl);
        }

        void call(Environment & env) { apply(); }

    private:

        uint8_t _cycle_duration = 0;
        uint8_t _indices_duration = 0;

        HCL _hcl;

        void wipe_indices(const HCL & hcl) {
            for(int i = 0; i < _indices_size; i++) {
                uint32_t idx = _indices[i];
                _output.set_pixel(idx, hcl.to_int());
            }
        }

        void set_indices() {
            for(int i = 0; i < _indices_size; i++) {
                _indices[i] = random(_output.size());
            }
            _indices_duration = multirandom(50, 4);
        }

        void set_color() {
            _hcl.clamp_hue(randomf(1.0));
            _hcl.clamp_chroma(0.5 + randomf(0.3));
        }

        void cycle() {
            _cycle_duration = 1 + multirandom(20, 3);
            _hcl.clamp_lum(randomf(0.1));
        }
    };
};

