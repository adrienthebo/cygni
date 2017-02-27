#include "platform.h"
#include "pin13.h"

uint8_t octo_pins[] = {2, 14, 7, 8, 6, 21, 22, 5};
uint8_t pin_count = 8;

using namespace pin13;

void bitBang(uint8_t pin, uint32_t delayPeriod) {
    for(int i = 0; i < pin; i++) {
        digitalWrite(pin, HIGH);
        delayMicroseconds(delayPeriod);
        digitalWrite(pin, LOW);
        delayMicroseconds(delayPeriod);
    }
}

void setup() {
    for(int idx = 0; idx < pin_count; idx++) {
        pinMode(octo_pins[idx], OUTPUT);
    }
    setup13();
}

int counter = 0;

void loop() {
    for(int idx = 0; idx < pin_count; idx++) {
        int pin = octo_pins[idx];
        bitBang(pin, 100);
    }

    blink13(1);
    counter = counter + 1 % 25;
}

int main() {
    setup();
    while(true) {
        loop();
    }
    return 0;
}

