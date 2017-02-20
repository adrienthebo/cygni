#pragma once

#include <cygni/hcl.hpp>
#include <cygni/util.hpp>
#include "effect.hpp"

namespace Cygni {

    /**
     * Effects whose state is independently determined on a per-pixel basis,
     * and whose state is stored on a per-pixel basis.
     *
     * ## Requirements
     *
     * Instances of T must provide the following.
     *
     * 1. A default constructor so that the class template can instantiate
     *    the nodes.
     *
     * 2. Instances of T must define a `#to_int() -> uint32` method that will
     *    convert the current pixel state to an RGB value.
     *
     * 3. Instances of T must define a `#step()` method to update the pixel
     *    state for the next frame.
     */
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

        virtual void call(Environment & env) { apply(); }

    protected:

        T *nodes;
    }; // struct Trunk
}; // namespace Cygni
