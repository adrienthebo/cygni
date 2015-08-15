#pragma once
#include <drivers/driver.h>
#include <effects/effect.h>
#include <grid.h>
#include <Color.h>
#include <util.h>

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

        void apply(Driver *driver) {
            if(--_indices_duration <= 0) {
                /* We're selecting a new set of indices. Reduce the brightness
                 * of the currently selected indices to reduce power
                 * consumption and offset the brightness of the next indices,
                 * and boost the saturation of the current indices to reduce
                 * the low sat Easter effect.
                 */
                wipe_indices(driver, _hue, _sat + 0.15, _lum * 0.25);
                set_indices();
                set_color();
            }

            if(--_cycle_duration > 0) {
                return;
            }

            cycle();
            wipe_indices(driver, _hue, _sat, _lum);
        }


    private:

        uint8_t _cycle_duration = 0;
        uint8_t _indices_duration = 0;

        float _lum;
        float _sat;
        float _hue;

        Color c;

        void wipe_indices(Driver *driver, float hue, float sat, float lum) {
            Color c;
            c.convert_hcl_to_rgb(hue, sat, lum);
            for(int i = 0; i < _indices_size; i++) {
                uint32_t idx = _indices[i];
                driver->set_pixel(idx, c.red, c.green, c.blue);
            }
        }

        void set_indices() {
            for(int i = 0; i < _indices_size; i++) {
                _indices[i] = random(50);
            }
            _indices_duration = multirandom(100, 3);
        }

        void set_color() {
            _hue = randomf(1.0);
            _sat = 0.5 + randomf(0.3);
        }

        void cycle() {
            _cycle_duration = 1 + multirandom(20, 2);
            _lum = randomf(0.1);
        }
    };
};

