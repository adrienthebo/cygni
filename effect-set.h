#include "platform.h"
#include <cygni/effects/effect.hpp>

namespace Cygni {
    struct EffectSet {

        EffectSet(uint32_t size) {
            _size = size;
            _list = new Effect*[_size];
        }

        EffectSet(uint32_t size, Effect *list[]) : EffectSet(size) {
            memcpy(_list, list, _size * sizeof(Effect *));
        }

        Effect * current() {
            return _list[_index];
        }

        void next_effect() {
            _index = (_index + 1) % _size;
        }

        uint32_t get_size() {
            return _size;
        }

        uint32_t get_index() {
            return _index;
        }

        void apply() {
            current()->apply();
        }

    private:

        /**
         * Thems effects which we be gettin, yo.
         */
        Effect **_list;

        uint32_t _size;

        /**
         * The index of the current effect.
         */
        uint32_t _index = 0;
    };
};
