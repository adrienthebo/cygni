#pragma once
#include <cygni/effects/trunk.hpp>
#include <cygni/hue.hpp>
#include <grid.h>

namespace Cygni {
    struct Zig : Effect {

        Zig(Output &output) : Effect(output) {
            _cur_idx = random(_output.size());
            _tgt_idx = random(_output.size());
            _ctr = 0;
            _hue = Hue();
        }

        void apply() {
            scale();

            _hue.next();

            if(move()) {
                _output.set_pixel(_cur_idx, 0xFFFFFF);
            } else {
                _output.set_pixel(_cur_idx, _hue.to_int());
            }
        }

        void call(Environment & env) { apply(); }

        /**
         * Returns true if we've reached our destination, false otherwise.
         */
        bool move() {
            if(_tgt_idx > _cur_idx) {
                ++_cur_idx;
            } else if(_tgt_idx < _cur_idx) {
                --_cur_idx;
            } else {
                _tgt_idx = random(_output.size());
                return true;
            }
            return false;
        }

    private:

        void scale() {
            RGB tmp;
            for(uint32_t i = 0; i < _output.size(); i++) {
                tmp.from_int(_output.get_pixel(i));
                tmp.scale(240);
                _output.set_pixel(i, tmp.to_int());
            }
        }

        Hue _hue;
        uint32_t _cur_idx;
        uint32_t _tgt_idx;
        uint32_t _ctr;
    };
};
