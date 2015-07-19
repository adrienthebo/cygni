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

        virtual int get_length() = 0;
    protected:

        int _length;
    };
};
