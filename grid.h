#pragma once

#include "platform.h"
#include "rgb.h"

namespace Cygni {

    struct Grid {

        Grid(int width, int height);

        int get_width();
        int get_height();
        int get_size();

        /**
         * Is this x index within the grid?
         */
        bool is_valid_x_index(uint32_t x);

        /**
         * Is this y index within the grid?
         */
        bool is_valid_y_index(uint32_t y);

        bool is_valid_position(uint32_t x, uint32_t y);

        bool is_valid_offset(uint32_t offset);

        RGB * get_pixel(uint32_t x, uint32_t y);

        RGB * get_pixel(uint32_t offset);

        void set_pixel(uint32_t x, uint32_t y, RGB * value);

        RGB * begin();
        RGB * end();

    protected:

        uint32_t _width;
        uint32_t _height;
        uint32_t _size;

        RGB *_grid;
    };
};
