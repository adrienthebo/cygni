#pragma once

#include "platform.h"

namespace Cygni {
    struct RGB {
        uint8_t red;
        uint8_t green;
        uint8_t blue;

        RGB() : red(0), green(0), blue(0) { }

        RGB(uint8_t r, uint8_t g, uint8_t b) : red(r), green(g), blue(b) { }

        RGB(uint32_t rgb) {
            from_int(rgb);
        }

        bool operator==(const RGB &other) {
            return red == other.red && green == other.green && blue == other.blue;
        }

        void fade(uint8_t fade_by) {
            red   -= fade_by;
            green -= fade_by;
            blue  -= fade_by;
        }

        /**
         *
         * @see https://github.com/FastLED/FastLED/blob/3.0.1/lib8tion.h#L705-L707
         */
        void scale(uint8_t scale_by) {
            red   = ((uint32_t)red * (uint32_t)scale_by) >> 8;
            green = ((uint32_t)green * (uint32_t)scale_by) >> 8;
            blue  = ((uint32_t)blue * (uint32_t)scale_by) >> 8;
        }

        void from_int(uint32_t val) {
            red   = (val & 0xFF0000) >> 16;
            green = (val & 0x00FF00) >> 8;
            blue  = (val & 0x0000FF);
        }

        uint32_t to_int() {
            return (red << 16) | (green << 8) | blue;
        }
    };
};
