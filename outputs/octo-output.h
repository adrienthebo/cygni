#pragma once

#include <drivers/octo-driver.h>
#include <outputs/output.h>

namespace Cygni {
    struct OctoOutput : Output {
        OctoOutput(OctoDriver &driver, uint32_t width, uint32_t height) : _driver(driver), _width(width), _height(height) {
            _size = _width * _height;
        }

        uint32_t width() {
            return _width;
        }

        uint32_t height() {
            return _height;
        }

        uint32_t size() {
            return _size;
        }

        virtual void set_pixel(int idx, int r, int g, int b) {
            _driver.set_pixel(idx, r, g, b);
        }

        virtual void set_pixel(int idx, int rgb) {
            _driver.set_pixel(idx, rgb);
        }

        virtual uint32_t get_pixel(uint32_t idx) {
            return _driver.get_pixel(idx);
        }

    private:

        OctoDriver &_driver;
        uint32_t _width;
        uint32_t _height;
        uint32_t _size;
    };
};
