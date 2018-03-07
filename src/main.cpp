#include <Arduino.h>
#include "Sensors.h"
#include "Display.h"
#include "Led.h"

Sensors sensors;
Display display;
Led led;

void setup() {
    Serial.begin(115200);
    sensors.initSensors();
    display.initDisplay();
    led.init();
}

void loop() {
    delay(50);
    sensors.tick();

    DhtReading dhtVal = sensors.getDhtReading();

    // format 4 positions with 1 decimal places
    char tempChar[5];
    dtostrf(dhtVal.temp, 4, 1, tempChar);
    char humidityChar[5];
    dtostrf(dhtVal.humidity, 4, 1, humidityChar);
    char heatIndexChar[5];
    dtostrf(dhtVal.heatIndex, 4, 1, heatIndexChar);
    char luxChar[6];
    float lux = sensors.getLightReading();
    dtostrf(lux, 5, 0, luxChar);

    String motionStr = sensors.getPirSensorReading()
        ? "Motion Detected"
        : "Motion Idle";

    if (sensors.wasButtonLongPressed()) {
        Serial.println("Button was long pressed");
    }
    if (sensors.wasButtonClicked()) {
        Serial.println("Button was clicked");
    }

    display.clear();
    String tempLine = "T:";
    tempLine += tempChar;
    tempLine += "  H:";
    tempLine += humidityChar;

    String heatIndexLine = "Heat Index: ";
    heatIndexLine += heatIndexChar;

    String luxLine = "Lux: ";
    luxLine += luxChar;

    display.setLineText(1, tempLine);
    display.setLineText(2, heatIndexLine);
    display.setLineText(3, luxLine);
    display.setLineText(4, motionStr);
    display.render();
    uint8_t ledIntensity = 127;

    if (lux < 500) {
        led.colorWipe({ 0, 0, ledIntensity }, 10);
    } else if (lux >= 500 && lux < 1000) {
        led.colorWipe({ 0, ledIntensity, 0 }, 10);
    } else {
        led.colorWipe({ ledIntensity, 0, 0 }, 10);
    }
}
