#include <DmxReceiver.h>
#include "pin13.h"
#include "vendor/cores/teensy3/kinetis.h"
#include "drivers/octo-driver.h"

#define STRIP_LENGTH 50
#define MAX_PIXELS 50 * 8

static constexpr uint8_t rs485_enable = 3;

DmxReceiver dmx;
IntervalTimer dmxTimer;
Cygni::OctoDriver *driver;
elapsedMillis elapsed;

void onFrame() {
    digitalWrite(LED_BUILTIN, HIGH);
    delayMicroseconds(2);
    digitalWrite(LED_BUILTIN, LOW);

    for(uint16_t dmx_offset = 0, led_offset = 0; dmx_offset < 512; dmx_offset += 3, ++led_offset) {
        driver->set_pixel(led_offset,
                dmx.getDimmer(dmx_offset + 1),
                dmx.getDimmer(dmx_offset + 2),
                dmx.getDimmer(dmx_offset + 3));
    }
    driver->show();
}

void onSecond() {
    elapsed -= 1000;
    Serial.printf("DMX frameCount=%d", dmx.frameCount());

    /* Display all nonzero DMX values */
    for (int i = 0; i < 512; i++) {
        uint8_t v = dmx.getDimmer(i);
        if (v) {
            Serial.printf(" %d:%d", i, v);
        }
    }
    Serial.printf("\n");
}

void dmxTimerISR(void)
{
    dmx.bufferService();
}

void setupUSBSerial() {
    Serial.begin(115200);
}

void setupDMX() {
    dmx.begin();
    /* Use a timer to service DMX buffers every 1ms */
    dmxTimer.begin(dmxTimerISR, 1000);
}

void setupWS2811() {
    driver = new Cygni::OctoDriver(MAX_PIXELS, STRIP_LENGTH);
    driver->clear();
    driver->show();
}

void setup() {
    setupUSBSerial();
    setupDMX();
    setupWS2811();
    pin13::setup13();
}

void loop() {
    if (dmx.newFrame()) {
        onFrame();
    }

    if (elapsed > 1000) {
        onSecond();
    }
}
