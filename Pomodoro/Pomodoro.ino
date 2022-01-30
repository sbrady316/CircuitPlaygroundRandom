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

enum Colors {
    Red     = 0xFF0000,
    Green   = 0x00FF00,
    Blue    = 0x0000FF,
};

SerialLogger sl;
PassThroughLogger logger(sl);
ConstantRenderer* crp = new ConstantRenderer();
unsigned long colors[ledCount];
IIntervalRenderer* irp = new RangedRenderer(10 * 1000, Red, colors, ledCount);

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

    //logger.LogArray("CRP ", crp->Render(5000), ledCount);
    logger.LogArray(0500, irp->Render(500), ledCount);
    logger.LogArray(1000, irp->Render(1000), ledCount);
    logger.LogArray(1500, irp->Render(1500), ledCount);
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
    irp->Render(timeRemaining);

    if (currentTime - lastUpdate > 100 && timeRemaining > -1000)
    {
        logger.LogArray(timeRemaining, colors, ledCount);
        lastUpdate = currentTime;
    }

    if (lightsOn)
    {
        for (size_t p = 0; p < ledCount; p++)
        {
            CircuitPlayground.setPixelColor(p, colors[p]);
        }
    }

}


