#include "platform.h"
#include "pin13.h"
#include "octo-driver.h"

#define STRIP_LENGTH 50
#define MAX_PIXELS 50 * 8

using namespace pin13;

Cygni::OctoDriver *driver;

void setup() {
    pinMode(13, OUTPUT);
    pulse13(5, 25);

    driver = new Cygni::OctoDriver(MAX_PIXELS, STRIP_LENGTH);
    driver->clear();
    driver->show();
}

int counter = 0;

int values[] = {0xFFFFFF, 0xFF0000, 0x00FF00, 0x0000FF, 0x000000};
int offset = 0;

void colorPixel(uint32_t index) {
    driver->set_pixel(index, values[offset % 5]);
}

void loop() {
    for(int idx = 0; idx < MAX_PIXELS; idx++) {
        if(idx % 5 == counter % 5) {
            colorPixel(idx);
        }
    }

    driver->show(50);
    ++offset;

    if(offset >= 5) {
        offset = 0;
        ++counter;
    }

    blink13(25);
}

int main() {
    setup();
    while(true) {
        loop();
    }
    return 0;
}
