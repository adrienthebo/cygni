#include "platform.h"
#include "grid.h"
#include "rgb.h"

namespace Cygni {
    Grid::Grid(int width, int height) {
        _width  = width;
        _height = height;
        _size   = _width * _height;
        _grid = new RGB[_size];
        memset(_grid, 0, _size * sizeof(RGB));
    }

    int Grid::get_width() {
        return _width;
    }

    int Grid::get_height() {
        return _height;
    }

    int Grid::get_size() {
        return _size;
    }

    bool Grid::is_valid_x_index(uint32_t x) {
        return x < _width;
    }

    bool Grid::is_valid_y_index(uint32_t y) {
        return y < _height;
    }

    bool Grid::is_valid_position(uint32_t x, uint32_t y) {
        return is_valid_x_index(x) && is_valid_y_index(y);
    }

    bool Grid::is_valid_offset(uint32_t offset) {
        return offset < _size;
    }

    void Grid::set_pixel(uint32_t x, uint32_t y, RGB * value) {
        if(!is_valid_position(x, y)) {
            return;
        }
        int idx = _width * y + x;
        _grid[idx] = *value;
    }

    RGB * Grid::get_pixel(uint32_t x, uint32_t y) {
        if(!is_valid_position(x, y)) {
            return 0;
        }
        int idx = _width * y + x;
        return &_grid[idx];
    }

    RGB * Grid::get_pixel(uint32_t offset) {
        if(!is_valid_offset(offset)) {
            return 0;
        }
        return &_grid[offset];
    }

    RGB * Grid::begin() {
        return &_grid[0];
    }

    RGB *Grid::end() {
        return &_grid[_size];
    }
};
