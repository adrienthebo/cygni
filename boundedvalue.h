#pragma once

namespace Cygni {
    template <typename T>
    struct BoundedValue {
        
        T min;
        T max;
        T by;
        T val;

        BoundedValue(T cmin, T cmax, T cby, T cval) :
            min(cmin), max(cmax), by(cby), val(cval) {};

        const T & step() {
            T next = val + by;
            if (next <= min || next >= max) {
                by = -by;
                next = next + by + by;
            }
            val = next;
            return val;
        }
    };
};
