#pragma once
#include <Color.h>

#include <util.h>
#include "effect.h"
#include "effects/trunk.h"
#include "boundedrand.h"

namespace Cygni {

    struct Leaf {

        Leaf() :
            _hue(0.55, 0.9, 0.0005),
            _lum(0.0, 0.05, 0.0005, 0.0)
            //_hue(0.3, 0.7, 0.0005),
            //_lum(0.0, 0.05, 0.0005, 0.0)
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

    struct Willow : public Cygni::Trunk<Leaf> {
        Willow(Output &output) : Cygni::Trunk<Leaf>(output)
        {}
    };
};
