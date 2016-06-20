#pragma once
#include <Color.h>

#include <util.h>
#include "effect.hpp"

namespace Cygni {

    template <typename T>
    struct Trunk : Cygni::Effect {

        Trunk(Output &output) : Effect(output) {
            nodes = new T[output.size()];
        }

        virtual void apply() {
            Color c;

            for(uint32_t i = 0, size = _output.size(); i < size; ++i) {
                T &node = nodes[i];
                node.step();
                c.convert_hcl_to_rgb(node.hue(), node.sat(), node.lum());
                _output.set_pixel(i, c.red, c.green, c.blue);
            }
        };

        void call(Environment & env) { apply(); }

        T *nodes;
    };
};

