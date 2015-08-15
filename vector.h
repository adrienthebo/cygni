#pragma once

#include <platform.h>

namespace Cygni {
    template<typename T>
    struct Vector {

        Vector(uint32_t size) {
            _size = size;
            _buffer = new T[_size];
            memset(_buffer, 0, _size * sizeof(T));
        };

        ~Vector() {
            delete[] _buffer;
        }

        T * get(uint32_t offset) {
            if(!is_valid_offset(offset)) {
                return nullptr;
            }
            return &_buffer[offset];
        }

        void set(uint32_t offset, T value) {
            if(!is_valid_offset(offset)) {
                return;
            }
            _buffer[offset] = value;
        }

        bool is_valid_offset(uint32_t offset) {
            return offset < _size;
        }

        uint32_t size() const {
            return _size;
        }

        T * begin() {
            return &_buffer[0];
        }

        T * end() {
            return &_buffer[_size];
        }

    protected:

        uint32_t _size;
        T *_buffer;
    };
};
