/*
 Name:		Pomodoro.ino
 Created:	1/17/2022 6:11:52 PM
 Author:	sbrady

 Timer app for doing the pomodoro technique
*/

#include <Adafruit_Circuit_Playground.h>
#include "PomodoroUtil.h"
#include "src\ConstantRenderer.h"
#include "src\RangedRenderer.h"
#include "src\CompositeRenderer.h"
#include "src\PassThroughLogger.h"

unsigned long endTime, lastUpdate = 0;

// Track if lights should be off
bool lightsOn = true;
RenderConfig* currentConfig = NULL;
RenderConfig** configurations = NULL;

const size_t ledCount = 10;


// the setup function runs once when you press reset or power the board
void setup() {
    Serial.begin(9600);
    CircuitPlayground.begin();
    logger.Log("Begin Setup");

    // turn off speaker when not in use
    CircuitPlayground.speaker.enable(false);
    // Geez, that's bright
    CircuitPlayground.setBrightness(10);

    configurations = new RenderConfig*[2]
    {
        new RenderConfig(
            new CompositeRenderer(
                new IIntervalRenderer * [3] {
                    new RangedRenderer(1000L * 10, Red, ledCount),
                    new RangedRenderer(1000L * 60, Green, ledCount),
                    new RangedRenderer(1000L * 60 * 30, Blue, ledCount),
                },
                3, ledCount
            ),
            1000L * 60 * 25, // 25 minutes for real pomodoro
            millis()
        ),
        new RenderConfig(
            new CompositeRenderer(
                new IIntervalRenderer * [3] {
                    new RangedRenderer(1000L * 10, Red, ledCount),
                    new RangedRenderer(1000L * 10, Green, ledCount),
                    new RangedRenderer(1000L * 20, Blue, ledCount),
                },
                3, ledCount
            ),
            1000L * 10, // 10 seconds for testing
            millis()
        ),
    };

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

    currentConfig = configurations[CircuitPlayground.slideSwitch()];

    long currentTime = millis();
    long timeRemaining = currentConfig->GetEndTime() - currentTime;
    auto colors = currentConfig->GetRenderer()->Render(timeRemaining);

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


