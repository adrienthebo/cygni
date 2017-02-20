#pragma once

#include <cygni/hue.hpp>
#include <cygni/effects/effect.hpp>
#include <cygni/util/boundedvalue.hpp>

namespace Cygni {
    /**
     * Creates a particle that bounces from the bottom to the top of the range,
     * and whose 'aura' randomly expands and contracts.
     */
    struct Wanderer : Effect {
        BoundedValue<float> _pos;
        BoundedRand<float> _radius;
        float _velocity;
        Hue _hue;

        Wanderer(Output &output) : 
            Effect(output), 
            _pos(0.0, _output.size(), 0.25, 5.0),
            _radius(4.0, _output.size() / 2, 0.1, 5.0) {
            _velocity = 0.0;
            _hue.set_incr(0.001);
            _hue.clamp_lum(0.3);
        }

        void apply() {
            _hue.step();
            _pos.step();
            _radius.step();
            for(uint32_t i = 0, size = _output.size(); i < size; ++i) {
                RGB tmp = scale(i, _hue.to_rgb());
                _output.set_pixel(i, tmp.to_int());
            }
        }

        void call(Environment & env) { apply(); }

        private:

        RGB scale(int32_t offset, const RGB & orig) {
            float distance = abs(_pos.val - offset);

            RGB rv = RGB(orig);

            if(distance > _radius.val) {
                // The pixel is entirely outside of the radius, black the pixel out.
                rv.scale(0);
            } else {
                float scale_factor = (_radius.val - distance) / _radius.val;
                rv.scale(255 * scale_factor);
            }
            return rv;
        }

    }; // struct Wanderer
}; // namespace Cygni

