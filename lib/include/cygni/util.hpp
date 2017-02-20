#pragma once

namespace Cygni {
    namespace Util {
        float randomf(float max) {
            return static_cast<float> (random() / static_cast<float> (RAND_MAX / max));
        }

        long multirandom(long max, int passes) {
            long rv = max;
            for(int i = 0; i < passes; i++) {
                rv = random(rv);
            }
            return rv;
        }
    };
};
