#pragma once

#include <cygni/util/range.hpp>

namespace Cygni {
    namespace Util {
        template <typename T>
        struct BoundedValue : public Range<T> {

            using Range<T>::min;
            using Range<T>::max;

            T by;
            T val;

            BoundedValue(T cmin, T cmax, T cby, T cval) :
                Range<T>(cmin, cmax), by(cby), val(cval) {};

            virtual const T & step() {
                T next = val + by;
                if (next <= min || next >= max) {
                    by = -by;
                    next = next + by + by;
                }
                val = next;
                return val;
            }
        }; // struct BoundedValue
    }; // namespace Util
}; // namespace Cygni
