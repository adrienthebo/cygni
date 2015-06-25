#include "platform.h"

void setup() {
    pinMode(13, OUTPUT);
    Serial.begin(9600);
}

int delayPeriod = 25;

void loop() {
    digitalWrite(13, HIGH);
    delay(delayPeriod);
    digitalWrite(13, LOW);
    delay(delayPeriod);
}

int main() {
    setup();
    while(true) {
        loop();
    }
    return 0;
}

