#pragma once
#include <driver.h>

namespace Cygni {
    struct Effect {
        virtual void apply(Cygni::OctoDriver *driver) = 0;
    };
};
