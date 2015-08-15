#pragma once

#include <platform.h>
#include <vector.h>

namespace Cygni {

    template<typename T>
    struct Matrix : protected Vector<T> {

        Matrix(uint32_t width, uint32_t height)
            : Vector<T>(width * height), _width(width), _height(height) { }
        
        bool is_valid_x_index(uint32_t x) {
            return x < _width;
        }

        bool is_valid_y_index(uint32_t y) {
            return y < _height;
        }

        bool is_valid_position(uint32_t x, uint32_t y) {
            return is_valid_x_index(x) && is_valid_y_index(y);
        }

        uint32_t size() const { return Vector<T>::_size; }

        uint32_t width() {
            return _width;
        }

        uint32_t height() {
            return _height;
        }

        T * get(uint32_t x, uint32_t y) {
            return Vector<T>::get(x + (y * _width));
        }

        void set(uint32_t x, uint32_t y, T value) {
            Vector<T>::set(x + (y * _width), value);
        }

        /** Forwarded methods to Vector<T> */

        T * get(uint32_t offset) {
            return Vector<T>::get(offset);
        }

        void set(uint32_t offset, T value) {
            Vector<T>::set(offset, value);
        }

        bool is_valid_offset(uint32_t offset) {
            return Vector<T>::is_valid_offset(offset);
        }

        T * begin() {
            return Vector<T>::begin();
        }

        T * end() {
            return Vector<T>::end();
        }

    private:

        uint32_t _width;
        uint32_t _height;
    };
}; 
   
   
