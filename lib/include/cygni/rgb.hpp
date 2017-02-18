#pragma once

#include "platform.h"
#include <cygni/pixel.hpp>

namespace Cygni {
    struct RGB : Pixel {
        uint8_t r = 0;
        uint8_t g = 0;
        uint8_t b = 0;

        uint8_t red() const;
        uint8_t green() const;
        uint8_t blue() const;

        RGB() = default;
        RGB(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}

        RGB(uint32_t rgb);

        bool operator==(const RGB &rhs) const;

        void fade(uint8_t fade_by);

        void scale(uint8_t scale_by);

        void from_int(uint32_t val);

        uint32_t to_int() const;
    }; // namespace RGB
}; // namespace Cygni
