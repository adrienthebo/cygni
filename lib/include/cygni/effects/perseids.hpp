#pragma once
#include "effect.hpp"
#include <Color.h>
#include <util.h>

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

            // TODO: add tests for this instead of a commented out, hack serial block.

            /*
            Serial.print("mass factor: ");
            Serial.print(_mass, DEC);
            Serial.print(" | ");
            Serial.print("heat factor: ");
            Serial.print(_heat, DEC);
            Serial.print(" | ");
            Serial.print("raw lum: ");
            Serial.print(raw_lum, DEC);
            Serial.print(" | ");
            Serial.print("scaled lum: ");
            Serial.print(scaled_lum, 2);
            Serial.println();
            */

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
            Color c;

            uint32_t step_to = _m->step();

            scale();

            c.convert_hcl_to_rgb(0.1, 0.99, _m->luminosity());

            _output.set_pixel(step_to, c.red, c.green, c.blue);
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
