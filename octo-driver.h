#pragma once
#include "driver.h"

#ifndef Arduino_h
#include <OctoWS2811.h>
#endif

namespace Cygni {
    struct OctoDriver : Driver {

        OctoDriver(int length, int strip_length);

        OctoDriver(int length, int strip_length, int flags);

        ~OctoDriver();

        void show() {
            _pixels->show();
        }

        void show(uint32_t duration) {
            show();
            delay(duration);
        }

        void set_pixel(int idx, int r, int g, int b) {
            _pixels->setPixel(idx, r, g, b);
        }

        void set_pixel(int idx, int rgb) {
            _pixels->setPixel(idx, rgb);
        }


        virtual void clear_pixel(int idx) {
            set_pixel(idx, 0, 0, 0);
        }

        virtual void clear() {
            for(int idx = 0; idx < _length; idx++) {
                clear_pixel(idx);
            }
        }


        bool is_busy() {
            return _pixels->busy();
        }

        virtual int get_length();

        protected:

        uint32_t *_frame_buf;
        uint32_t *_draw_buf;
        int _strip_length;
        int _flags;

        OctoWS2811 *_pixels;
    };
};
