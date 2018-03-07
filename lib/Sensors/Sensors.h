#ifndef SENSORS_H
#define SENSORS_H
#include "DHT.h"
#include <Wire.h> //BH1750 IIC Mode
#include <Button.h>        //https://github.com/JChristensen/Button

struct DhtReading {
    float temp;
    float humidity;
    float heatIndex;
};

class Sensors {
    private:
        bool buttonLongPressed = false;
        bool buttonClicked     = false;
        DhtReading latestValue = {};
    public:
        Sensors();
        void initSensors();
        void tick();
        DhtReading getDhtReading();
        float getLightReading();
        int getPirSensorReading();
        bool wasButtonClicked();
        bool wasButtonLongPressed();
};

#endif
