#pragma once

namespace Cygni {
    namespace Util {
        template <typename T>
        struct BoundedRand {

            T min;
            T max;
            T by;
            T val;
            T tgt;

            BoundedRand(T min, T max, T by, T val, T tgt) : min(min), max(max), by(by), val(val), tgt(tgt) {}
            BoundedRand(T min, T max, T by, T val) : BoundedRand(min, max, by, val, randomf(max - min) + min) {}
            BoundedRand(T min, T max, T by) : BoundedRand(min, max, by, randomf(max - min) + min) {}

            const T & step() {
                if(val < tgt) {
                    lt();
                }
                else if(val > tgt) {
                    gt();
                }
                else {
                    tgt = randomf(max - min) + min;
                }

                return val;
            }

            void lt() {
                T next = val + by;

                if(next >= tgt) {
                    tgt = randomf(max - min) + min;
                }
                else {
                    val = next;
                }
            }

            void gt() {
                T next = val - by;

                if(next <= tgt) {
                    tgt = randomf(max - min) + min;
                }
                else {
                    val = next;
                }
            }
        }; // struct BoundedRand
    }; // namespace Util
}; // namespace Cygni
