#pragma once

#include <cygni/effects/effect.hpp>
#include <cygni/hcl.hpp>
#include <cygni/util.hpp>

using namespace Cygni::Util;

namespace Cygni {

    // Private
    struct Meteor {

        Meteor(uint32_t max) {
            _max = max;
            regen();
        }

        float luminosity() {
            uint32_t mass_factor = _mass - (max_mass / 2);
            uint32_t heat_factor = _heat - (max_heat / 2);

            uint32_t raw_lum = ((mass_factor * mass_factor) + (heat_factor * heat_factor));

            float scaled_lum = static_cast<float>(raw_lum / 8) / max_luminosity;

            return scaled_lum;
        };

        uint32_t step() {
            _pos = wrap(_pos, _velocity, _max);

            burn();

            if(_mass <= 0) {
                regen();
            }

            return floor(_pos);
        };

        float _pos;
        float _velocity;

        uint32_t _mass;
        uint32_t _heat;

        uint32_t _max; // The maximum range to wrap over

    private:

        static constexpr uint32_t max_mass = 300;
        static constexpr uint32_t max_heat = 300;
        static constexpr uint32_t max_luminosity = (max_mass / 2) * (max_heat / 2);

        void burn() {
            _mass -= 1;
            _heat += 1;
        }

        void regen() {
            _heat = 0;
            _mass = random(max_mass / 2) + max_mass / 2;
            _velocity = (randomf(2.0) - 1.00);
            _pos = randomf(_max);
        }

        /**
         * @param pos The starting position
         * @param distance The distance to move by (positive or negative)
         * @param max The interval to wrap over
         */
        float wrap(float pos, float distance, float max) {
            float delta = pos + distance;
            if(delta < 0.0) {
                return max + delta;
            } else if (delta >= max) {
                return delta - max;
            } else {
                return delta;
            }
        }
    };

    struct Perseids : Effect {
        Perseids(Output &output) : Effect(output) {
            _m = new Meteor(_output.size());
        }

        void apply() {
            HCL c { 0.1, 0.99, _m->luminosity() };

            uint32_t step_to = _m->step();

            scale();

            _output.set_pixel(step_to, c.to_int());
        }

        void call(Environment & env) { apply(); }

    private:

        // TODO STOP COPY/PASTING THIS GODDAMMIT
        void scale() {
            RGB tmp;
            for(uint32_t i = 0; i < _output.size(); i++) {
                tmp.from_int(_output.get_pixel(i));
                tmp.scale(254);
                _output.set_pixel(i, tmp.to_int());
            }
        }


        Meteor *_m;
    };
};
