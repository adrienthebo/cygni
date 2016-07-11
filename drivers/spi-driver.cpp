#include <SPI.h>

#define RED 0
#define GREEN 1
#define BLUE 2

#define NUM_LEDS 4800

namespace Cygni {
    struct SPIDriver {

        SPIDriver() {
            // Pure cargo culting. Deal with this later.
            pinMode(10, OUTPUT);
            pinMode(11, OUTPUT);

            memset(LED_Array, 0, NUM_LEDS);

            SPI.begin();
            SPI.setClockDivider(SPI_CLOCK_DIV2);
            delay(500);
        }

        void show() {
            sync_frame();
        }

        void set_pixel(int column, int row, int r, int g, int b) {
            set_LED_RGB(column, row, r, g, b);
        }

    private:

        int LED_Array[NUM_LEDS];

        // Begin sorrow and regret
        void set_LED(uint16_t column, uint16_t row, uint16_t color, uint16_t intensity)
        {
            uint16_t LED_position;
            uint16_t bitmask;
            bitmask = 0x80 >> row;
            LED_position = 24*column + (color * 8);

            LED_Array[LED_position] &= ~bitmask;
            LED_Array[LED_position + 1] &= ~bitmask;
            LED_Array[LED_position + 2] &= ~bitmask;
            LED_Array[LED_position + 3] &= ~bitmask;
            LED_Array[LED_position + 4] &= ~bitmask;
            LED_Array[LED_position + 5] &= ~bitmask;
            LED_Array[LED_position + 6] &= ~bitmask;
            LED_Array[LED_position + 7] &= ~bitmask;

            if(intensity & 0x80)
                LED_Array[LED_position] |= bitmask; // MSB
            if(intensity & 0x40)
                LED_Array[LED_position + 1] |= bitmask; //
            if(intensity & 0x20)
                LED_Array[LED_position + 2] |= bitmask; //
            if(intensity & 0x10)
                LED_Array[LED_position + 3] |= bitmask; //
            if(intensity & 0x08)
                LED_Array[LED_position + 4] |= bitmask; //
            if(intensity & 0x04)
                LED_Array[LED_position + 5] |= bitmask; //
            if(intensity & 0x02)
                LED_Array[LED_position + 6] |= bitmask; //
            if(intensity & 0x01)
                LED_Array[LED_position + 7] |= bitmask; //

        }

        void set_LED_RGB(uint16_t column, uint16_t row, uint16_t red_intensity, uint16_t green_intensity, uint16_t blue_intensity)
        {
            set_LED(column, row, RED, red_intensity);
            set_LED(column, row, GREEN, green_intensity);
            set_LED(column, row, BLUE, blue_intensity);
        }

        void sync_frame() {
            for(size_t i = 0; i < NUM_LEDS; ++i) {
                SPI.transfer(LED_Array[i]);
            }
            delay(100);
        }

        void clear_frame() {
            for(size_t i = 0; i < NUM_LEDS; ++i) {
                LED_Array[i] = 0;
            }
            sync_frame();
        }

    };
};
