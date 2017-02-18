#pragma once

#include "platform.h"

#include <cygni/pixel.hpp>
#include <cygni/rgb.hpp>

namespace Cygni {
    /**
     * A refactored version of https://github.com/lucidtronix/ColorArduino
     *
     * The original implementation of this library has good color range, but the implementation
     * is cryptic and undocumented. This implementation has some minor cleanup and refactoring
     * and builds in range clamping to prevent nonsensical values.
     */
    struct HCL : Pixel {

        HCL() = default;

        HCL(float h, float c, float l) : _hue(h), _chroma(c), _lum(l) {}

        HCL(const HCL & rhs);

        void clamp_hue(const float & hue);
        void clamp_hue_by(const float & delta);

        void clamp_chroma(const float & chroma);
        void clamp_chroma_by(const float & delta);

        void clamp_lum(const float & lum);
        void clamp_lum_by(const float & delta);

        uint32_t to_int() const;

        RGB to_rgb() const;

        float hue() const;
        float chroma() const;
        float lum() const;

        protected:

        float clamp(const float & in) const;

        private:

        float _hue = 0;
        float _chroma = 0;
        float _lum = 0;

        float magic_float_normalize(const float in, const float magic1, const float magic2) const;
    };
};
