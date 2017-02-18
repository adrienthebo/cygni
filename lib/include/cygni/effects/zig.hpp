#pragma once
#include <cygni/effects/trunk.hpp>
#include <cygni/hue.hpp>
#include <grid.h>

namespace Cygni {
    struct Zig : Effect {

        const int SCALE_FACTOR = 2;

        Zig(Output &output) : Effect(output) {
            _position = random(_output.size() * SCALE_FACTOR);
            _target = random(_output.size() * SCALE_FACTOR);
            _hue = Hue();
            _hue.clamp_lum(0.1);
            _hue.set_incr(0.001);
        }

        void apply() {
            _hue.next();

            if(move()) {
                _output.set_pixel(_position / SCALE_FACTOR, 0xFFFFFF);
            } else {
                _output.set_pixel(_position / SCALE_FACTOR, _hue.to_int());
            }
        }

        void call(Environment & env) { apply(); }

        /**
         * Returns true if we've reached our destination, false otherwise.
         */
        bool move() {
            if(_target > _position) {
                ++_position;
            } else if(_target < _position) {
                --_position;
            } else {
                _target = random(_output.size() * SCALE_FACTOR);
                return true;
            }
            return false;
        }

    private:

        int clamp(int cl) {
            while(cl > 10) { cl -= 10; }
            return cl;
        }

        Hue _hue;
        uint32_t _position;
        uint32_t _target;
    };
};
