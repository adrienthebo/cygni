#pragma once

namespace pin13 {
    void setup13() {
        pinMode(13, OUTPUT);
    }

    void blink13(int duration) {
        digitalWrite(13, HIGH);
        delay(duration);
        digitalWrite(13, LOW);
        delay(duration);
    }

    void pulse13(int count, int duration) {
        for(int i = 0; i < count; i++) blink13(duration);
    }
};
