#pragma once

namespace Cygni {
    namespace Util {
        template<typename T>
        struct Range {
            T min;
            T max;

            Range(T min, T max) : min(min), max(max) { }
        }; // struct Range
    }; // namespace Util
}; // namespace Cygni
