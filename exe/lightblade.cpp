#include "platform.h"
#include "pin13.h"

#include <drivers/spi-driver.hpp>
#include <outputs/spi-output.hpp>
#include <cygni/effects.hpp>

using namespace pin13;

Cygni::SPIDriver *driver;
Cygni::SPIOutput *output;
Cygni::Effect *e;

void setup() {

    /* Initialize onboard LED */
    pinMode(13, OUTPUT);
    pulse13(100, 25);


    driver = new Cygni::SPIDriver();
    driver->clear();
    driver->show();
}
//
//    output = new Cygni::SPIOutput(*driver, 50, 1);
//
//    Cygni::Output &q = *output;
//
//    e = new Cygni::Willow(q);
//}
//
void loop() {
    pulse13(100, 100);
}

//void loop() {
//    e->apply();
//    driver->show(10);
//    while(driver->is_busy());
//}

int main() {
    setup();
    while(true) {
        loop();
    }
    return 0;
}
