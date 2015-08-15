#pragma once
#include <platform.h>

namespace Cygni {
    struct Output {

        virtual uint32_t width() = 0;
        virtual uint32_t height() = 0;
        virtual uint32_t size() = 0;

        virtual void set_pixel(int idx, int r, int g, int b) = 0;

        virtual void set_pixel(int idx, int rgb) = 0;

        virtual uint32_t get_pixel(uint32_t idx) = 0;

        virtual void clear_pixel(int idx) {
            set_pixel(idx, 0, 0, 0);
        }

        virtual void clear() {
            for(uint32_t idx = 0; idx < size(); idx++) {
                clear_pixel(idx);
            }
        }

    };
};
