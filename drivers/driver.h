#pragma once

namespace Cygni {
    struct Driver {

        Driver(int length) {
            _length = length;
        }

        virtual void show() = 0;

        virtual bool is_busy() {
            return false;
        }


        virtual void set_pixel(int idx, int r, int g, int b) = 0;
        virtual void set_pixel(int idx, int rgb) = 0;

        virtual uint32_t get_pixel(uint32_t idx) = 0;

        virtual void clear() = 0;

        virtual int get_length() = 0;
    protected:

        int _length;
    };
};
