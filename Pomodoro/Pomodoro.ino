/*
 Name:		Pomodoro.ino
 Created:	1/17/2022 6:11:52 PM
 Author:	sbrady

 Timer app for doing the pomodoro technique
*/

#include "RangedRenderer.h"
#include <Adafruit_Circuit_Playground.h>
#include "src\ConstantRenderer.h"

unsigned long endTime, lastUpdate = 0;
const size_t ledCount = 10;
const long updateIntervalMs = 500;
unsigned int loops = 0;

// Track if lights should be off
bool lightsOn = true;

ConstantRenderer* crp = new ConstantRenderer();

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

    Serial.print("Colors:");
    auto& colors = crp->Render(0);
    for (size_t p = 0; p < ledCount; p++)
    {
        Serial.print(colors[p]); Serial.print(" ");
    }
    Serial.println();
}

void loop() {
    // Manage lights
    if (CircuitPlayground.leftButton())
    {
        lightsOn = true;
    }
    else if (CircuitPlayground.rightButton())
    {
        lightsOn = false;
        CircuitPlayground.clearPixels();
    }

    long currentTime = millis();
    long timeRemaining = endTime - currentTime;
    auto& colors = crp->Render(timeRemaining);
    if (lightsOn)
    {
        for (size_t p = 0; p < ledCount; p++)
        {
            CircuitPlayground.setPixelColor(p, colors[p]);
        }
    }

    /*
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
    */
}
