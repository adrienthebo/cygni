#pragma once

#include <cygni/hcl.hpp>
#include <util.h>
#include "effect.hpp"

namespace Cygni {

    template <typename T>
    struct Trunk : Cygni::Effect {

        Trunk(Output &output) : Effect(output) {
            nodes = new T[output.size()];
        }

        virtual void apply() {
            for(uint32_t i = 0, size = _output.size(); i < size; ++i) {
                T &node = nodes[i];
                node.step();
                _output.set_pixel(i, node.to_int());
            }
        };

        void call(Environment & env) { apply(); }

        T *nodes;
    };
};

