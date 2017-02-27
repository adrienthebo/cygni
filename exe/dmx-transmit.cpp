#include "platform.h"

static constexpr uint8_t rs485_enable = 3;

#include <TeensyDmx.h>

#define DMX_REDE 3

byte DMXVal[] = {0xFE};

TeensyDmx Dmx(Serial1, DMX_REDE);

void setup() {
  Dmx.setMode(TeensyDmx::DMX_OUT);
}

void loop() {
  Dmx.setChannels(0, DMXVal, 1);
  Dmx.loop();
}
