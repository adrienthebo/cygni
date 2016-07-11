#pragma once

#include <drivers/spi-driver.hpp>
#include <outputs/output.h>

namespace Cygni {
    struct SPIOutput : Output {
        SPIOutput(SPIDriver &driver, uint32_t width, uint32_t height) : _driver(driver), _width(width), _height(height) {
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
            int strip = idx / 200;
            int offset = idx % 200;
            _driver.set_pixel(offset, strip, r, g, b);
        }

        virtual void set_pixel(int idx, int rgb) {
            int r = (rgb & 0xFF0000) >> 16;
            int g = (rgb & 0xFF00) >> 8;
            int b = (rgb & 0xFF);
            set_pixel(idx, r, g, b);
        }

        virtual uint32_t get_pixel(uint32_t idx) {
            return 0;
        }


    private:

        SPIDriver &_driver;
        uint32_t _width;
        uint32_t _height;
        uint32_t _size;
    };
};
