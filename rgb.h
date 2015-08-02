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

        uint32_t to_int() {
            return (red << 16) | (green << 8) | blue;
        }
    };
};
