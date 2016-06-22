#pragma once

#include <cygni/pixel.hpp>
#include <cygni/rgb.hpp>

namespace Cygni {
/**
 * I HAVE NO IDEA WHAT I'M FUCKING DOING
 * THIS SHIT WAS RIPPED OFF FROM THE MYSTERIOUS ARDUINO COLOR LIBRARY
 * I'LL GIVE CREDIT LATER
 *
 * BUT OH MY GOD I AM FUCKING BAFFLED.
 */
struct HCL : Pixel {

    HCL() = default;

    HCL(float h, float c, float l) : _hue(h), _chroma(c), _lum(l) {}

    void clamp_hue_by(const float & delta) {
        _hue = clamp(_hue + delta);
    }

    void clamp_chroma_by(const float & delta) {
        _chroma = clamp(_chroma + delta);
    }

    void clamp_lum_by(const float & delta) {
        _lum = clamp(_lum + delta);
    }

    uint32_t to_int() const {
        float redf, greenf, bluef;

        // unsaturated
        if (_chroma == 0) {
            redf = greenf = bluef = _lum;
        }

        float temp2;
        if (_lum < 0.5) {
            temp2 = _lum * (1 + _chroma);
        } else {
            temp2 = _lum + _chroma - _lum * _chroma;
        }

        float temp1 = 2.0 * _lum - temp2;
        float rtemp = clamp(_hue + 0.33333);
        float gtemp = clamp(_hue);
        float btemp = clamp(_hue - 0.33333);

        redf = magic_float_normalize(rtemp, temp1, temp2);
        greenf = magic_float_normalize(gtemp, temp1, temp2);
        bluef = magic_float_normalize(btemp, temp1, temp2);

        uint8_t red, green, blue;
        red = (uint8_t) (255 * redf);
        green = (uint8_t) (255 * greenf);
        blue = (uint8_t) (255 * bluef);

        return (red << 16) | (green << 8) | blue;
    }

    RGB to_rgb() const {
        return RGB(to_int());
    }

    protected:

    float clamp(const float & in) const {
        float rv = in;
        while(rv > 1) rv -= 1;
        while(rv < 0) rv += 1;
        return rv;
    }

    float _hue = 0;
    float _chroma = 0;
    float _lum = 0;


    private:

    float magic_float_normalize(const float in, const float magic1, const float magic2) const {
        float rv;
        if (6.0 * in < 1) {
            rv = magic1 + (magic2 - magic1) * 6.0 * in;
        } else if (2.0 * in < 1) {
            rv = magic2;
        } else if (3.0 * in < 2 ) {
            rv = magic1 + (magic2 - magic1) * (0.6666 - in) * 6.0;
        }
        else {
            rv = magic1;
        }
        return rv;
    }
};
};
