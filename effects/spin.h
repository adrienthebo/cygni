#pragma once
#include <drivers/driver.h>
#include "effect.h"
#include <Color.h>
#include <hue.h>

namespace Cygni {
    struct Spin : Cygni::Effect {

        Spin() {
            _h.set_incr(0.001);
        }

        void apply(Driver *driver) {
            uint32_t idx = ++_counter % 50;


            driver->set_pixel(idx, _h.red(), _h.green(), _h.blue());

            if(_counter % 2 == 0) {
                scale(driver);
            }
            _h.next();
        }

    private:

        uint32_t _counter = 0;
        Hue _h;

        void scale(Driver *driver) {
            RGB tmp;
            for(int i = 0; i < 50; i++) {
                tmp.from_int(driver->get_pixel(i));
                tmp.scale(240);
                driver->set_pixel(i, tmp.to_int());
            }
        }
    };
};

