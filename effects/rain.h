#pragma once
#include <drivers/driver.h>
#include "effect.h"
#include <Color.h>
#include <util.h>

using namespace Cygni::Util;

namespace Cygni {

    struct Drop {

        Drop() {
            _idx = 0; // Non-insane default behavior. Perhaps.
            _level = randomf(1.0);
        }

        uint32_t _idx;
        float _level;

        void next() {
            _level -= 0.01;
            if(_level <= 0.0) {
                _level += 1.0;
            }
        }

        float get_sat() {
            return 1.0 - _level * _level;
        }

        float get_lum() {
            return _level / 4;
        }
    };

    struct Rain : Cygni::Effect {

        Rain(Output &output) : Effect(output) {
            for(uint32_t i = 0; i < _size; i++) {
                _drops[i]._idx = random(50);
            }
        }

        void apply(Driver *driver) {
            Color c;

            for(uint32_t i = 0; i < _size; i++) {
                Drop &d = _drops[i];

                c.convert_hcl_to_rgb(0.6, d.get_sat(), d.get_lum());

                driver->set_pixel(d._idx, c.red, c.green, c.blue);

                if(d._level <= 0.01) {
                    d._idx = random(50);
                }
                d.next();
            }
        }

    private:

        static constexpr uint32_t _size = 10;
        Drop _drops[_size];
    };
};

