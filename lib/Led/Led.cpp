#include "Led.h"

#define PIXEL_PIN   D7
#define PIXEL_COUNT 8

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

// Fill the dots one after the other with a color
void Led::colorWipe(Color c, uint8_t wait) {
    for(uint16_t i=0; i<strip.numPixels(); i++) {
        uint32_t color = strip.Color(c.r, c.g, c.b);
        strip.setPixelColor(i, color);
        strip.show();
        delay(wait);
    }
}

Led::Led() {

}

void Led::init() {
    strip.begin();
    strip.show();
}
