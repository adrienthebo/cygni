#pragma once
#include <drivers/driver.h>

#include <outputs/output.h>
#include <cygni/environment.hpp>

namespace Cygni {
    struct Effect {
        Effect(Output &output) : _output(output) { }

        virtual void apply() = 0;

        // TODO: make env const?
        virtual void call(Environment & env) = 0;

    protected:

        Output &_output;
    };
};
