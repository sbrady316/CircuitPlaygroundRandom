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
IIntervalRenderer* irp = new RangedRenderer(1000L * 60 * 25, Red, colors, ledCount);

// the setup function runs once when you press reset or power the board
void setup() {
    Serial.begin(9600);
    logger.Log("Begin Setup");

    CircuitPlayground.begin();

    // turn off speaker when not in use
    CircuitPlayground.speaker.enable(false);

    // Geez, that's bright
    CircuitPlayground.setBrightness(10);

    endTime = millis() + 1000L * 60 * 25;

    //logger.LogArray("CRP ", crp->Render(5000), ledCount);
    logger.LogArray( 983, irp->Render(983), ledCount);
    logger.LogArray(1000, irp->Render(1000), ledCount);
    logger.LogArray(1983, irp->Render(1983), ledCount);
    
    // Investigate why reds are F'd up on device only
    //auto rr = new RangedRenderer(10 * 1000, Red, colors, ledCount);
    //unsigned long sentinel = 0xAA1122BB;
    //logger.Log("Size Check: (%d) 0x%08lX, %i, %li", sizeof(unsigned long), sentinel, sentinel, sentinel);
    //logger.Log("0x%04X %04X", (uint16_t)(sentinel >> 16), (uint16_t)(sentinel & 0x0000FFFF));
    //logger.Log("0.983: 0x%08lX", rr->Fade(Red, 0.983));
    //logger.Log("0.500: 0x%08lX", rr->Fade(Red, 0.500));
    //logger.Log("0.283: 0x%08lX", rr->Fade(Red, 0.283));

    logger.Log("End Setup");
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

    if (currentTime - lastUpdate > 100) // && timeRemaining > -1000)
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


