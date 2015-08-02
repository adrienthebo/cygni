#pragma once

#include "platform.h"

namespace Cygni {
    struct RGB {
        uint8_t red;
        uint8_t green;
        uint8_t blue;

        bool operator==(const RGB &other) {
            return red == other.red && green == other.green && blue == other.blue;
        }

        void fade(uint8_t fade_by) {
            red   -= fade_by;
            green -= fade_by;
            blue  -= fade_by;
        }

        uint32_t to_int() {
            return (red << 16) | (green << 8) | blue;
        }
    };
};
