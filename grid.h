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
         *
         * @todo accept uint32_t, remove negative index check
         */
        bool is_valid_x_index(int x);

        /**
         * Is this y index within the grid?
         *
         * @todo accept uint32_t, remove negative index check
         */
        bool is_valid_y_index(int y);

        bool is_valid_position(int x, int y);

        bool is_valid_offset(uint32_t offset);

        RGB * get_pixel(int x, int y);

        RGB * get_pixel(uint32_t offset);

        void set_pixel(int x, int y, RGB * value);

        RGB * begin();
        RGB * end();


    protected:

        // TODO: uint32_t
        int _width;
        int _height;
        int _size;

        RGB *_grid;
    };
};
