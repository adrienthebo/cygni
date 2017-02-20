#pragma once

#include <cygni/effects/effect.hpp>
#include <cygni/hcl.hpp>
#include <cygni/util.hpp>

using namespace Cygni::Util;

namespace Cygni {

    struct Spark {

        Spark() {
            _idx = 0; // Non-insane default behavior. Perhaps.
            _level = randomf(1.0);
        }

        uint32_t _idx;
        float _level;

        void fade() {
            _level -= 0.004;
            if(_level <= 0.0) {
                _level += 0.7 - randomf(0.25);
            }
        }

        float get_sat() {
            return 1.0 - _level * _level;
        }

        float get_lum() {
            return _level / 4;
        }
    };

    struct Sparks : Cygni::Effect {

        Sparks(Output &output) : Effect(output) {
            for(uint32_t i = 0; i < _size; i++) {
                _drops[i]._idx = random(output.size());
            }
        }

        void apply() {

            for(uint32_t i = 0; i < _size; i++) {
                Spark &d = _drops[i];

                HCL hcl { 0.06, 0, 0 };
                hcl.clamp_chroma_by(d.get_sat());
                hcl.clamp_lum_by(d.get_lum());

                _output.set_pixel(d._idx, hcl.to_int());

                if(d._level <= 0.01) {
                    _output.clear_pixel(d._idx);
                    d._idx = random(_output.size());
                }
                d.fade();
            }
        }

        void call(Environment & env) { apply(); }
    private:

        static constexpr uint32_t _size = 25;
        Spark _drops[_size];
    };
};


