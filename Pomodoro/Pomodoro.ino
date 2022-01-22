/*
 Name:		Pomodoro.ino
 Created:	1/17/2022 6:11:52 PM
 Author:	sbrady

 Timer app for doing the pomodoro technique
*/

#include <Adafruit_Circuit_Playground.h>
#include <Adafruit_CircuitPlayground.h>

bool pinLevel = HIGH;
long endTime;

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

// the loop function runs over and over again until power down or reset
void loop() {
    pinLevel = !pinLevel;
    CircuitPlayground.redLED(pinLevel);
    delay(500);
}
