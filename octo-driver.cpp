#include "octo-driver.h"

namespace Cygni {
    OctoDriver::OctoDriver(int length, int strip_length) : OctoDriver(length, strip_length, WS2811_RGB) { }

    OctoDriver::OctoDriver(int length, int strip_length, int flags) : Driver(length) {
        _strip_length = strip_length;
        _flags = flags;

        int buffer_size = _length * 6;

        _frame_buf = new uint32_t[buffer_size];
        _draw_buf  = new uint32_t[buffer_size];

        _pixels = new OctoWS2811(_strip_length, _frame_buf, _draw_buf, _flags);
        _pixels->begin();
    }

    OctoDriver::~OctoDriver() {
        delete _frame_buf;
        delete _draw_buf;
        delete _pixels;
    }
};
