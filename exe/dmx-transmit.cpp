#include "platform.h"
#include <TeensyDmx.h>

#include "pin13.h"
using namespace pin13;

static constexpr uint8_t rs485_enable = 3;

byte DMXVal[] = {0xFE};

TeensyDmx Dmx(Serial1, rs485_enable);

void setup() {
    setup13();
    Dmx.setMode(TeensyDmx::DMX_OUT);
}

void loop() {
    Dmx.setChannels(0, DMXVal, 1);
    Dmx.loop();
    pulse13(50, 2);
}
