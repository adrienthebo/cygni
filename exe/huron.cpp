#include "platform.h"
#include "pin13.h"
#include "octo-driver.h"
#include <Color.h>
#include <Bounce.h>

#define STRIP_LENGTH 50
#define MAX_PIXELS 50 * 8

using namespace pin13;

struct Effect {
    virtual void apply(Cygni::OctoDriver *driver) = 0;
};

struct Whoa : Effect {
    
    float hue = 0;
    //float sat = 0.9;
    float sat = 0.9;
    float lum = 0.1;

    /*
     * How much to increment the hue for each index. Higher values mean faster
     * transitions through the spectrums, meaning a more compressed transition.
     */
    float hue_scale = 0.0101;

    /*
     * How much to decrement the luminosity for each index. Higher values mean
     * smaller bands of light and dark. Very low values mean the entire panel
     * will fade from light to dark.
     */
    float lum_scale = 0.0101;

    virtual void apply(Cygni::OctoDriver *d) {
        Color c;
        for(int i = 0; i < d->get_length(); i++) {
            hue = increment_hue(hue);
            lum = decrement_lum(lum);
            c.convert_hcl_to_rgb(hue, sat, lum);
            d->set_pixel(i, c.red, c.green, c.blue);
        }
    }

protected:

    float increment_hue(float current) {
        float sum = current + hue_scale;
        if(sum >= 0.4) {
            sum--;
        }
        return sum;
    }

    float decrement_lum(float current) {
        return 0.005;
        float sum = current - lum_scale;
        if(sum <= 0.00001) {
            sum += 0.4;
        }
        return sum;
    }
};

Cygni::OctoDriver *driver;
Whoa dude;

void setup() {
    pinMode(13, OUTPUT);
    pulse13(5, 25);

    driver = new Cygni::OctoDriver(MAX_PIXELS, STRIP_LENGTH);
    driver->clear();
    driver->show();
}

void loop() {
    dude.apply(driver);
    driver->show(50);
    while(driver->is_busy());
}

int main() {
    setup();
    while(true) {
        loop();
    }
    return 0;
}
