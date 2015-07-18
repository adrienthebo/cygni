#include "platform.h"
#include "pin13.h"
#include "octo-driver.h"
#include <Color.h>

#define STRIP_LENGTH 5
#define MAX_PIXELS 5 * 8

Cygni::OctoDriver *driver;

void setup() {
    pinMode(13, OUTPUT);
    pulse13(5, 25);

    driver = new Cygni::OctoDriver(STRIP_LENGTH * 8, STRIP_LENGTH);
    driver->clear();
    driver->show();
}

void strobeIndex(uint32_t pixel_index) {
    int duration = 250;

    driver->set_pixel(pixel_index, 0x808080);
    driver->show(duration);

    driver->set_pixel(pixel_index, 255, 0, 0);
    driver->show(duration);

    driver->set_pixel(pixel_index, 0, 255, 0);
    driver->show(duration);

    driver->set_pixel(pixel_index, 0, 0, 255);
    driver->show(duration);

    driver->clear_pixel(pixel_index);
}

void strobeRange() {
    int duration = 250;
    for(int idx = 0; idx < MAX_PIXELS; idx++) {
        driver->set_pixel(idx, 255, 255, 255);
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

int group_from_index(int idx) {
    return idx / 5;
}

void loop() {
    for(int idx = 0; idx < MAX_PIXELS; idx++) {
        if(group_from_index(idx) % 2 == 0) {
            strobeIndex(idx);
        }
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
