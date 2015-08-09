#include "platform.h"
#include "pin13.h"
#include "octo-driver.h"
#include "effects/effect.h"
#include "effects/shift.h"
#include "effects/zig.h"
#include "effects/stutter.h"
#include "effects/spin.h"
#include "effects/chase.h"
#include "effect-set.h"

#include <Bounce2.h>

#define STRIP_LENGTH 50
#define MAX_PIXELS 50 * 8

using namespace pin13;

Cygni::OctoDriver *driver;
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

    /* Configure LEDs and effects */
    Cygni::Effect *effects[] = {
        new Cygni::Chase(),
        new Cygni::Spin(),
        new Cygni::Stutter(),
        new Cygni::Zig(),
        new Cygni::Shift(),
    };

    es = new Cygni::EffectSet(5, effects);

    driver = new Cygni::OctoDriver(MAX_PIXELS, STRIP_LENGTH);
    driver->clear();
    driver->show();
}

void loop() {
    button.update();
    if(button.fell()) {
        es->next_effect();
    }

    es->apply(driver);
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
