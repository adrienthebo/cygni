#pragma once

#include "rgb.h"

namespace Cygni {

    struct Grid {

        Grid(int width, int height);

        int get_width();
        int get_height();
        int get_size();

        RGB & get_pixel(int x, int y);
        void set_pixel(int x, int y, RGB value);

        bool is_valid_x_index(int x);
        bool is_valid_y_index(int y);

        bool is_valid_position(int x, int y);

    protected:

        // TODO: uint32_t
        int _width;
        int _height;
        int _size;

        RGB *_grid;
    };
};
