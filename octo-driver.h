#include "driver.h"

#ifndef Arduino_h
#include <OctoWS2811.h>
#endif

namespace Cygni {
    struct OctoDriver : Driver {

        OctoDriver(int length, int strip_length) : OctoDriver(length, strip_length, WS2811_RGB) { }

        OctoDriver(int length, int strip_length, int flags) : Driver(length) {
            _strip_length = strip_length;
            _flags = flags;

            int buffer_size = _length * 6;

            _frame_buf = new uint32_t[buffer_size];
            _draw_buf  = new uint32_t[buffer_size];

            _pixels = new OctoWS2811(_strip_length, _frame_buf, _draw_buf, _flags);
            _pixels->begin();
        }

        ~OctoDriver() {
            delete _frame_buf;
            delete _draw_buf;
            delete _pixels;
        }

        void show() {
            _pixels->show();
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

        protected:

        uint32_t *_frame_buf;
        uint32_t *_draw_buf;
        int _strip_length;
        int _flags;

        OctoWS2811 *_pixels;
    };
};
