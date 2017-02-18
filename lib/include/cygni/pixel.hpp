#pragma once

#include "platform.h"

namespace Cygni  {
    struct Pixel {
        virtual uint32_t to_int() const = 0;
    };
};
