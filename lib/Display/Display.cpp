#include "Display.h"
#define PIN_DISPLAY_CLOCK D1
#define PIN_DISPLAY_DATA  D2

// U8g2 Contructor list is available here: https://github.com/olikraus/u8g2/wiki/u8g2setupcpp
// U8G2_R0 == No Rotation
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, PIN_DISPLAY_CLOCK, PIN_DISPLAY_DATA, U8X8_PIN_NONE);


// #define textFont u8g2_font_7x13_tf
// #define iconFont u8g2_font_7x13_t_symbols

#define textFont u8g2_font_unifont_t_symbols
#define iconFont u8g2_font_unifont_t_symbols
const uint16_t fontHeight = 16;
// https://github.com/olikraus/u8g2/wiki/u8g2reference#drawglyph
const uint16_t symbolTempCel = 0x2103;
const uint16_t symbolTempFar = 0x2109;
const uint16_t symbolLux     = 0x25cd;

const uint16_t symbolSun  = 0x2600;
const uint16_t symbolSun2 = 0x2604;

const uint16_t symbolRect0     = 0x2580;
const uint16_t symbolRect1     = 0x2581;
const uint16_t symbolRect2     = 0x2582;
const uint16_t symbolRect3     = 0x2583;
const uint16_t symbolRect4     = 0x2584;
const uint16_t symbolRect5     = 0x2585;
const uint16_t symbolRect6     = 0x2586;
const uint16_t symbolRect7     = 0x2587;
const uint16_t symbolRect8     = 0x2588;
const uint16_t symbolRect9     = 0x2589;

const uint16_t symbolPhone1   = 0x260e;
const uint16_t symbolPhone2   = 0x260f;

const uint16_t symbolCheck   = 0x2713;
const uint16_t symbolCheck2  = 0x2714;
const uint16_t symbolCheckX  = 0x2715;
const uint16_t symbolCheckX2 = 0x2716;

void Display::setLineText(int lineNumber, String text) {
    u8g2.setFontMode(1);
    u8g2.setFontDirection(0);
    u8g2.setFont(textFont);
    if (lineNumber < 4) {
        // u8g2.setFontPosTop();
        u8g2.setFontPosBottom();
        u8g2.drawStr(0, fontHeight * lineNumber, text.c_str());
    } else {
        u8g2.setFontPosBottom();
        u8g2.drawStr(0, 64, text.c_str());
    }
}

void Display::clear() {
    u8g2.clearBuffer();
}

void Display::render() {
    u8g2.sendBuffer();
}

Display::Display() {

}

void Display::initDisplay() {
    u8g2.begin();
}
