/*
 Name:		Pomodoro.ino
 Created:	1/17/2022 6:11:52 PM
 Author:	sbrady

 Timer app for doing the pomodoro technique
*/

#include <Adafruit_Circuit_Playground.h>

bool pinLevel = HIGH;
unsigned long endTime, lastUpdate = 0;
const long updateIntervalMs = 500;
unsigned int loops = 0;


// the setup function runs once when you press reset or power the board
void setup() {
    Serial.begin(9600);
    Serial.println("Circuit Playground test!");

    CircuitPlayground.begin();

    // turn off speaker when not in use
    CircuitPlayground.speaker.enable(false);

    // Geez, that's bright
    CircuitPlayground.setBrightness(10);

    endTime = millis() + 5 * 1000;
}

void loop() {
    long currentTime = millis();
    long timeRemaining = endTime - currentTime;
    long wholeSecondsRemaining = timeRemaining / 1000;
    for (uint8_t p = 0; p < wholeSecondsRemaining; p++)
    {
        CircuitPlayground.setPixelColor(p, 0xFF, 0, 0);
    }

    CircuitPlayground.setPixelColor(wholeSecondsRemaining, 0xFF * (timeRemaining % 1000) / 1000, 0, 0);

    loops++;
    if (currentTime - lastUpdate > updateIntervalMs && timeRemaining > 0)
    {
        pinLevel = !pinLevel;
        CircuitPlayground.redLED(pinLevel);
        Serial.print("loops / interval = "); Serial.println(loops);

        lastUpdate = currentTime;
        loops = 0;
    }
}
