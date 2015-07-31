#pragma once

#include "platform.h"

namespace Cygni {
    struct RGB {
        // TODO: uint8_t
        int red;
        int green;
        int blue;

        bool operator==(const RGB &other) {
            return red == other.red && green == other.green && blue == other.blue;
        }
    };
};
