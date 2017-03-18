#include "platform.h"
#include <TeensyDmx.h>

#include "pin13.h"
using namespace pin13;

static constexpr uint8_t rs485_enable = 3;

byte DMXVal[] = {0x01};

TeensyDmx Dmx(Serial1, rs485_enable);

static uint8_t ctr = 0;

void setup() {
    setup13();
    Dmx.setMode(TeensyDmx::DMX_OUT);
}

void loop() {
    for(uint16_t offset = 0; offset < 512; ++offset) {
        Dmx.setChannel(offset, ctr);
    }
    pulse13(50, 2);
    if(++ctr >= 32) {
        ctr = 0;
    }
}
