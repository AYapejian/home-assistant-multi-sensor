#ifndef DISPLAY_H
#define DISPLAY_H
#include <SPI.h>
#include "U8g2lib.h"

class Display {
    private:

    public:
        Display();
        void initDisplay();
        void clear();
        void setLineText(int lineNumber, String text);
        void render();
};

#endif
