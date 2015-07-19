#include "platform.h"
#include "pin13.h"
#include "octo-driver.h"

#define STRIP_LENGTH 5
#define MAX_PIXELS 5 * 8

using namespace pin13;

Cygni::OctoDriver *driver;

void setup() {
    pinMode(13, OUTPUT);
    pulse13(5, 25);

    driver = new Cygni::OctoDriver(STRIP_LENGTH * 8, STRIP_LENGTH);
    driver->clear();
    driver->show();
}

void strobeIndex(uint32_t pixel_index) {
    int duration = 50;

    driver->set_pixel(pixel_index, 128, 128, 128);
    if(pixel_index % 5 == 0) {
        driver->show(4 * duration);
    } else {
        driver->show(duration);
    }

    driver->set_pixel(pixel_index, 255, 0, 0);
    driver->show(duration);

    driver->set_pixel(pixel_index, 0, 255, 0);
    driver->show(duration);

    driver->set_pixel(pixel_index, 0, 0, 255);
    driver->show(duration);

    driver->clear_pixel(pixel_index);
}

void strobeRange() {
    int duration = 500;
    for(int idx = 0; idx < MAX_PIXELS; idx++) {
        driver->set_pixel(idx, 128, 128, 128);
    }
    driver->show(duration);

    for(int idx = 0; idx < MAX_PIXELS; idx++) {
        driver->set_pixel(idx, 255, 0, 0);
    }
    driver->show(duration);

    for(int idx = 0; idx < MAX_PIXELS; idx++) {
        driver->set_pixel(idx, 0, 255, 0);
    }
    driver->show(duration);

    for(int idx = 0; idx < MAX_PIXELS; idx++) {
        driver->set_pixel(idx, 0, 0, 255);
    }
    driver->show(duration);

    for(int idx = 0; idx < MAX_PIXELS; idx++) {
        driver->clear_pixel(idx);
    }
}

void loop() {
    blink13(5);

    for(int idx = 0; idx < MAX_PIXELS; idx++) {
        strobeIndex(idx);
    }
    strobeRange();
}

int main() {
    setup();
    while(true) {
        loop();
    }
    return 0;
}
