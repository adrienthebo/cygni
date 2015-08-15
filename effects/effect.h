#pragma once
#include <drivers/driver.h>

#include <outputs/output.h>

namespace Cygni {
    struct Effect {
        Effect(Output &output) : _output(output) { }

        virtual void apply(Cygni::Driver *driver) = 0;

    protected:

        Output &_output;
    };
};
