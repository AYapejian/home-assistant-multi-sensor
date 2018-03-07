#include "Sensors.h"
#define DHTTYPE DHT22

#define BUTTON_PULLUP     true
#define BUTTON_INVERT     true
#define BUTTON_DEBOUNCE   20
#define BUTTON_LONG_PRESS 1000

#define PIN_SCL         D1
#define PIN_SDA         D2
#define PIN_PIR_SENSOR  D6
#define PIN_DHT_SENSOR  D5
#define PIN_BUTTON      D4

#define ADDRESS_BH1750 0x23

DHT dht(PIN_DHT_SENSOR, DHTTYPE);
Button theButton(PIN_BUTTON, BUTTON_PULLUP, BUTTON_INVERT, BUTTON_DEBOUNCE);

Sensors::Sensors() {

}


static const unsigned long REFRESH_INTERVAL = 2000;
static       unsigned long lastRefreshTime  = 0;

// Returns all based on celsius
DhtReading Sensors::getDhtReading() {

    if(millis() - lastRefreshTime >= REFRESH_INTERVAL) {
		lastRefreshTime += REFRESH_INTERVAL;
        float temp      = dht.readTemperature();
        float humidity  = dht.readHumidity();
        float heatIndex = dht.computeHeatIndex(temp, humidity, false);
        latestValue = { temp, humidity, heatIndex };
	}

    return latestValue;

}

float Sensors::getLightReading() {
    int i = 0;
    uint16_t val=0;
    byte buff[2];

    Wire.beginTransmission(ADDRESS_BH1750);
    Wire.write(0x10);            //1lx reolution 120ms
    Wire.endTransmission();

    Wire.beginTransmission(ADDRESS_BH1750);
    Wire.requestFrom(ADDRESS_BH1750, 2);

    while(Wire.available()) {
        buff[i] = Wire.read();
        i++;
    }
    Wire.endTransmission();
    if (i == 2) {
        val = ((buff[0]<<8) | buff[1]) / 1.2;
    } else {
        val = -1;
    }

    return val;
}


int Sensors::getPirSensorReading() {
    return digitalRead(PIN_PIR_SENSOR);
}

bool Sensors::wasButtonLongPressed() {
    return buttonLongPressed;
}
bool Sensors::wasButtonClicked() {
    return buttonClicked;
}

// Needs logic work
void Sensors::tick() {
    theButton.read();
    buttonLongPressed = false;
    buttonClicked     = false;

    if (theButton.wasReleased()) {
        if(theButton.pressedFor(BUTTON_LONG_PRESS)) {
            buttonLongPressed = true;
            buttonClicked = false;
        } else {
            buttonLongPressed = false;
            buttonClicked = true;
        }
    }
}

void Sensors::initSensors() {
    Wire.begin(PIN_SDA, PIN_SCL);
    dht.begin();
    pinMode(PIN_PIR_SENSOR, INPUT);
    return;
}
