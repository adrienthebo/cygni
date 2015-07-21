#include "platform.h"
#include "pin13.h"
#include "octo-driver.h"
#include <Color.h>
#include <Bounce.h>
#include "effects/effect.h"
#include "effects/shift.h"

#define STRIP_LENGTH 50
#define MAX_PIXELS 50 * 8

using namespace pin13;

Cygni::OctoDriver *driver;
Cygni::Shift dude;

void setup() {
    pinMode(13, OUTPUT);
    pulse13(5, 25);

    driver = new Cygni::OctoDriver(MAX_PIXELS, STRIP_LENGTH);
    driver->clear();
    driver->show();
}

void loop() {
    dude.apply(driver);
    driver->show(100);
    while(driver->is_busy());
}

int main() {
    setup();
    while(true) {
        loop();
    }
    return 0;
}
