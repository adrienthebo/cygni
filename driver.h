#pragma once

namespace Cygni {
    struct Driver {

        virtual void show() = 0;

        virtual bool is_busy() {
            return false;
        }
    };
};
