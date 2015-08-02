#pragma once
#include <driver.h>

namespace Cygni {
    struct Effect {
        virtual void apply(Cygni::Driver *driver) = 0;
    };
};
