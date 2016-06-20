#pragma once

namespace Cygni {
    struct Environment {
        /// The time  it took to render the last frame
        unsigned long int last_render;

        /// The brightness scaling factor
        uint8_t brightness = 0;
    };
};

