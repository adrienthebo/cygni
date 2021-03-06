#include "platform.h"
#include "pin13.h"

#include <drivers/octo-driver.h>
#include <outputs/octo-output.h>

#include <cygni/effects.hpp>
#include <cygni/effect-set.hpp>

#include <Bounce2.h>

#define STRIP_LENGTH 50
#define MAX_PIXELS 50 * 8

using namespace pin13;

Cygni::OctoDriver *driver;
Cygni::Output *output;
Cygni::EffectSet *es;

Bounce next_button;
Bounce prev_button;

void setup() {

    srand(analogRead(0));

    /* Prepare buttons */
    pinMode(23, INPUT_PULLUP);
    next_button.attach(23);
    next_button.interval(5);

    pinMode(22, INPUT_PULLUP);
    prev_button.attach(22);
    prev_button.interval(5);

    /* Initialize onboard LED */
    pinMode(13, OUTPUT);
    pulse13(5, 25);

    driver = new Cygni::OctoDriver(MAX_PIXELS, STRIP_LENGTH);
    driver->clear();
    driver->show();

    output = new Cygni::OctoOutput(*driver, 50, 1);

    Cygni::Output &q = *output;

    /* Configure LEDs and effects */
    Cygni::Effect *effects[] = {
        new Cygni::Wanderer(q),
        new Cygni::PeriodicSplit(q),
        new Cygni::ZigFade(q),
        new Cygni::NightSky(q),
        new Cygni::Sparks(q),
        new Cygni::Shift(q),
        new Cygni::Willow(q),
        new Cygni::Periodic(q),
        new Cygni::Autumn(q),
        new Cygni::Spectrum(q),
        new Cygni::Rain(q),
        new Cygni::Cedar(q),
        new Cygni::Zig(q),
        new Cygni::Perseids(q),
        //new Cygni::Spin(q),
        //new Cygni::Chase(q),
        //new Cygni::Stutter(q),
    };

    es = new Cygni::EffectSet(14, effects);
}

void loop() {
    next_button.update();
    prev_button.update();
    if(next_button.fell()) {
        driver->clear();
        es->next_effect();
    } else if(prev_button.fell()) {
        driver->clear();
        es->prev_effect();
    }

    es->apply();
    driver->show(10);
    while(driver->is_busy());
}

int main() {
    setup();
    while(true) {
        loop();
    }
    return 0;
}
