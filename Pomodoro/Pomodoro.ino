/*
 Name:		Pomodoro.ino
 Created:	1/17/2022 6:11:52 PM
 Author:	sbrady

 Timer app for doing the pomodoro technique
*/

#include <Adafruit_Circuit_Playground.h>
#include "src\ConstantRenderer.h"
#include "src\RangedRenderer.h"
#include "src\PassThroughLogger.h"

unsigned long endTime, lastUpdate = 0;
const size_t ledCount = 10;
const long updateIntervalMs = 500;
unsigned int loops = 0;

// Track if lights should be off
bool lightsOn = true;

class SerialLogger : public ILogSink
{
    virtual void Log(const char* message)
    {
        Serial.print(message);
    }
};

SerialLogger sl;
PassThroughLogger logger(sl);
ConstantRenderer* crp = new ConstantRenderer();
IIntervalRenderer* irp = new RangedRenderer(10 * 1000, 0xFF0000);

// the setup function runs once when you press reset or power the board
void setup() {
    Serial.begin(9600);
    Serial.println("Circuit Playground test!");

    CircuitPlayground.begin();

    // turn off speaker when not in use
    CircuitPlayground.speaker.enable(false);

    // Geez, that's bright
    CircuitPlayground.setBrightness(10);

    endTime = millis() + 12 * 1000;

    logger.LogArray("CRP", crp->Render(5000), ledCount);
    logger.LogArray("0500", irp->Render(500), ledCount);
    auto* colors = irp->Render(5000);
    logger.LogArray("5000", colors, ledCount);
    logger.LogArray("6500", irp->Render(6500), ledCount);
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
    auto* colors = irp->Render(timeRemaining);
    if (lightsOn)
    {
        for (size_t p = 0; p < ledCount; p++)
        {
            CircuitPlayground.setPixelColor(p, colors[p]);
        }
    }
}


