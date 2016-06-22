#pragma once

#include <cygni/pixel.hpp>

namespace Cygni {
    struct RGB : Pixel {
        uint8_t red() { return r; }
        uint8_t green() { return g; }
        uint8_t blue() { return b; }

        uint8_t r = 0;
        uint8_t g = 0;
        uint8_t b = 0;

        RGB() = default;
        RGB(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}

        RGB(uint32_t rgb) {
            from_int(rgb);
        }

        bool operator==(const RGB &rhs) {
            return r == rhs.r && g == rhs.g && b == rhs.b;
        }

        void fade(uint8_t fade_by) {
            r -= fade_by;
            g -= fade_by;
            b -= fade_by;
        }

        /**
         *
         * @see https://github.com/FastLED/FastLED/blob/3.0.1/lib8tion.h#L705-L707
         */
        void scale(uint8_t scale_by) {
            r   = ((uint32_t)r * (uint32_t)scale_by) >> 8;
            g = ((uint32_t)g * (uint32_t)scale_by) >> 8;
            b  = ((uint32_t)b * (uint32_t)scale_by) >> 8;
        }

        void from_int(uint32_t val) {
            r = (val & 0xFF0000) >> 16;
            g = (val & 0x00FF00) >> 8;
            b = (val & 0x0000FF);
        }

        uint32_t to_int() const {
            return (r << 16) | (g << 8) | b;
        }
    };
};
