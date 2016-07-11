#pragma once

#include <SPI.h>

namespace Cygni {
    struct SPIDriver {

        SPIDriver();

        void show();

        void show(uint32_t duration) {
            show();
            delay(duration);
        }

        void set_pixel(int column, int row, int r, int g, int b);

        virtual void clear_pixel(int column, int row) {
            set_pixel(column, row, 0, 0, 0);
        }

        virtual void clear() {
            for(int strip = 0; strip < 7; strip++) {
                for(int offset = 0; offset < 200; offset++) {
                    clear_pixel(offset, strip);
                }
            }
        }

        bool is_busy() {
            return false;
        }

        virtual int get_length();
    };
};


