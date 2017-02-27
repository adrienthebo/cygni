#include "platform.h"
#include "pin13.h"

uint8_t octo_pins[] = {2, 14, 7, 8, 6, 21, 22, 5};
uint8_t pin_count = 8;

using namespace pin13;

void setup() {
    for(int idx = 0; idx < pin_count; idx++) {
        pinMode(octo_pins[idx], OUTPUT);
    }
    setup13();
}

void loop() {
    digitalWrite(13, HIGH);
    for(int idx = 0; idx < pin_count; idx++) {
        digitalWrite(octo_pins[idx], HIGH);
    }
    delay(3000);

    digitalWrite(13, LOW);
    for(int idx = 0; idx < pin_count; idx++) {
        digitalWrite(octo_pins[idx], LOW);
    }
    delay(1000);
}

int main() {
    setup();
    while(true) {
        loop();
    }
    return 0;
}


