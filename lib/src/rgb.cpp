#include <cygni/rgb.hpp>

namespace Cygni {

    uint8_t RGB::red() const { return r; }
    uint8_t RGB::green() const { return g; }
    uint8_t RGB::blue() const { return b; }

    RGB::RGB(uint32_t rgb) {
        from_int(rgb);
    }

    bool RGB::operator==(const RGB &rhs) const {
        return r == rhs.r && g == rhs.g && b == rhs.b;
    }

    void RGB::fade(uint8_t fade_by) {
        r -= fade_by;
        g -= fade_by;
        b -= fade_by;
    }

    /**
     *
     * @see https://github.com/FastLED/FastLED/blob/3.0.1/lib8tion.h#L705-L707
     */
    void RGB::scale(uint8_t scale_by) {
        r   = ((uint32_t)r * (uint32_t)scale_by) >> 8;
        g = ((uint32_t)g * (uint32_t)scale_by) >> 8;
        b  = ((uint32_t)b * (uint32_t)scale_by) >> 8;
    }

    void RGB::from_int(uint32_t val) {
        r = (val & 0xFF0000) >> 16;
        g = (val & 0x00FF00) >> 8;
        b = (val & 0x0000FF);
    }

    uint32_t RGB::to_int() const {
        return (r << 16) | (g << 8) | b;
    }
}; // namespace Cygni
