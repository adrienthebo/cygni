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

    protected:

        int _length;
    };
};
