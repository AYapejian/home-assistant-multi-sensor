#ifndef LED_H
#define LED_H
#include "Adafruit_NeoPixel.h"

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

class Led {
    private:

    public:
        Led();
        void init();
        void clear();
        void colorWipe(Color c, uint8_t wait);
        // void setLineText(int lineNumber, String text);
        // void render();
};

#endif
