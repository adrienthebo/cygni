/* This file intentionally left blank */

#ifdef Arduino_h
#include <OctoWS2811.h>
#endif

#include "platform.h"
#include "octo-driver.h"
#include "grid.h"

Cygni::OctoDriver *driver;

void blink(int duration) {
    digitalWrite(13, HIGH);
    delay(duration);
    digitalWrite(13, LOW);
    delay(duration);
}

void pulse(int count, int duration) {
    for(int i = 0; i < count; i++) blink(duration);
}

void setup() {
    pinMode(13, OUTPUT);
    pulse(5, 25);

    driver = new Cygni::OctoDriver(50 * 8, 50);
    driver->clear();
    driver->show();
}

void loop() {
    blink(100);

    driver->set_pixel(1, 128, 0, 0);
    driver->show();

    delay(100);
    driver->clear_pixel(1);
    driver->show();
    delay(100);
}
