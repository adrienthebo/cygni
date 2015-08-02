#pragma once
#include <driver.h>
#include <effects/effect.h>
#include <grid.h>
#include <hue.h>

namespace Cygni {
    struct Zig : Effect {

        Zig() {
            _cur_idx = random(50);
            _tgt_idx = random(50);
            _ctr = 0;
            _hue = Hue();
        }

        void apply(OctoDriver *driver) {
            if(++_ctr < 10) {
                return;
            } else {
                _ctr = 0;
            }

            if(move()) {
                driver->clear();
            } else {
                _hue.next();
                driver->set_pixel(_cur_idx, _hue.red(), _hue.green(), _hue.blue());
            }
        }

        /**
         * Returns true if we've reached our destination, false otherwise.
         */
        bool move() {
            if(_tgt_idx > _cur_idx) {
                ++_cur_idx;
            } else if(_tgt_idx < _cur_idx) {
                --_cur_idx;
            } else {
                _tgt_idx = random(50);
                return true;
            }
            return false;
        }

    private:

        Hue _hue;
        uint32_t _cur_idx;
        uint32_t _tgt_idx;
        uint32_t _ctr;
    };
};
