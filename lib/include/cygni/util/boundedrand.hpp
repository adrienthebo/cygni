#pragma once

namespace Cygni {
    namespace Util {
        /**
         * Randomly walk between values in a bounded range.
         */
        template <typename T>
        struct BoundedRand {

            /// The range minimum value
            T min;
            /// The range maximum value
            T max;
            /// The value to increment/decrement by on each step
            T by;
            /// The current position in the range
            T val;
            /// The desired position in the range that we're approaching
            T tgt;

            BoundedRand(T min, T max, T by, T val, T tgt) : min(min), max(max), by(by), val(val), tgt(tgt) {}
            BoundedRand(T min, T max, T by, T val) : BoundedRand(min, max, by, val, randomf(max - min) + min) {}
            BoundedRand(T min, T max, T by) : BoundedRand(min, max, by, randomf(max - min) + min) {}

            /**
             * Take the next step within our range. If the target value is reached then select
             * a new target value.
             *
             * \return The current position in the range.
             */
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

        private:

            /**
             * Take a step towards a target that's less than our current position. If taking the
             * step would reach or pass the target, reset the target.
             */
            void lt() {
                T next = val + by;

                if(next >= tgt) {
                    tgt = randomf(max - min) + min;
                }
                else {
                    val = next;
                }
            }

            /**
             * Take a step towards a target that's greater than our current position. If taking the
             * step would reach or pass the target, reset the target.
             */
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
