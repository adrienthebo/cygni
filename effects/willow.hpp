#pragma once

#include "effects/trunk.hpp"
#include "boundedrand.h"

namespace Cygni {

    struct WillowLeaf {

        WillowLeaf() :
            _hue(0.55, 0.9, 0.0005),
            _lum(0.0, 0.05, 0.0005, 0.0)
        {}

        void step() {
            _hue.step();
            _lum.step();
        }

        float hue() {
           return _hue.val;
        } 

        float sat() {
            return 0.9;
        }

        float lum() {
            return _lum.val;
        }

    private:

        BoundedRand<float> _hue;
        BoundedRand<float> _lum;
    };

    struct Willow : public Cygni::Trunk<WillowLeaf> {
        Willow(Output &output) : Cygni::Trunk<WillowLeaf>(output)
        {}
    };
};
