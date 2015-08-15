#include "platform.h"
#include "pin13.h"

#include <drivers/octo-driver.h>
#include <outputs/octo-output.h>

#include "effects/effect.h"
#include "effects/shift.h"
#include "effects/zig.h"
#include "effects/stutter.h"
#include "effects/spin.h"
#include "effects/chase.h"
#include "effects/rain.h"
#include "effect-set.h"

#include <Bounce2.h>

#define STRIP_LENGTH 50
#define MAX_PIXELS 50 * 8

using namespace pin13;

Cygni::OctoDriver *driver;
Cygni::Output *output;
Cygni::EffectSet *es;

Bounce button;

void setup() {
    /* Prepare debounced button */
    pinMode(12, INPUT_PULLUP);
    button.attach(12);
    button.interval(5);

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
        new Cygni::Rain(q),
        new Cygni::Chase(q),
        new Cygni::Spin(q),
        new Cygni::Stutter(q),
        new Cygni::Zig(q),
        new Cygni::Shift(q),
    };

    es = new Cygni::EffectSet(6, effects);

}

void loop() {
    button.update();
    if(button.fell()) {
        driver->clear();
        es->next_effect();
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
