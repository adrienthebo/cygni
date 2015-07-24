#include "platform.h"
#include "effects/effect.h"

namespace Cygni {
    struct EffectSet {

        EffectSet(uint32_t size) {
            _index = 0;
            _size = size;
            _list = new Effect*[_size];
        }

        Effect * current() {
            return _list[_index];
        }

        uint32_t get_size() {
            return _size;
        }

    private:

        uint32_t _size;
        Effect **_list;

        /**
         * Points to the current effect
         */
        uint32_t _index;
    };
};
