#include "grid.h"
#include "rgb.h"

namespace Cygni {
    Grid::Grid(int width, int height) {
        _width  = width;
        _height = height;
        _size   = _width * _height;
        _grid = new RGB[_size];
        // TODO: memset grid
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

    bool Grid::is_valid_x_index(int x) {
        return x >= 0 && x < _width;
    }

    bool Grid::is_valid_y_index(int y) {
        return y >= 0 && y < _height;
    }

    bool Grid::is_valid_position(int x, int y) {
        return is_valid_x_index(x) && is_valid_y_index(y);
    }
};
