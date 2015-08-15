#pragma once
#include <drivers/driver.h>

namespace Cygni {
    struct Effect {
        virtual void apply(Cygni::Driver *driver) = 0;
    };
};
