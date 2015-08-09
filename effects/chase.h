#pragma once
#include <driver.h>
#include "effect.h"
#include <Color.h>
#include <hue.h>

namespace Cygni {
    struct Chase : Cygni::Effect {

        void apply(Driver *driver) {
            if(++_delay % 5 != 0) {
                return;
            }

            scale(driver);

            uint32_t distance = 50 / _count;

            float hue = 0.0;
            for(uint32_t i = 0; i < _count; i++) {
                hue += 1.0 / 6;
                Color c;
                c.convert_hcl_to_rgb(hue, _sat, _lum);

                uint32_t idx = m_index(_counter + (i * distance));
                driver->set_pixel(idx, c.red, c.green, c.blue);
            }
            ++_counter;
        }

    private:

        float _sat = 0.9;
        float _lum = 0.05;

        uint32_t _count = 6;

        uint32_t m_index(uint32_t in) {
            return in % 50;
        }

        uint32_t _counter = 0;
        uint32_t _delay = 0;

        void scale(Driver *driver) {
            RGB tmp;
            for(int i = 0; i < 50; i++) {
                tmp.from_int(driver->get_pixel(i));
                tmp.scale(192);
                driver->set_pixel(i, tmp.to_int());
            }
        }
    };
};


