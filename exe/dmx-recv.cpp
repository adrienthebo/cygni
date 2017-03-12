#include <TeensyDmx.h>
#include "pin13.h"
#include "vendor/cores/teensy3/kinetis.h"

static constexpr uint8_t rs485_enable = 3;
static constexpr uint16_t dmx_offset = 0;

byte DMXVal[] = {0xFE};

using namespace pin13;

TeensyDmx Dmx(Serial1);

void setup() {
    pinMode(rs485_enable, OUTPUT);
    digitalWrite(rs485_enable, LOW);

    Dmx.setMode(TeensyDmx::DMX_IN);
    setup13();
}

void loop() {
    Dmx.loop();
    if (Dmx.newFrame()) {
        digitalWrite(13, HIGH);
        delayMicroseconds(3);
        digitalWrite(13, LOW);
        //pulse13(1, 1);
    } else {
        yield();
    }
}
