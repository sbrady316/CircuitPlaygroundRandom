#include <Adafruit_CircuitPlayground.h>
#include <stdio.h>

const uint8_t TAP_THRESHOLD = 40;
const uint32_t TAP_COLOR = 0x00FF00;
const uint32_t defaultColor = 0x2F002F;
const uint32_t touchColor = 0x0000FF;
const unsigned long interval = 100;

// we light one pixel at a time, this is our counter
uint8_t pixeln = 0;
uint8_t color = 0;
bool pinLevel = HIGH;
volatile uint8_t tapCount = 0;

// Keep track of updates
unsigned long previousUpdate = 0;
bool isLoggingLoop = false;

//
// Setup
//
void setup() {
    Serial.begin(9600);
    Serial.println("Circuit Playground test!");

    CircuitPlayground.begin();

    // turn off speaker when not in use
    CircuitPlayground.speaker.enable(false);

    // Geez, that's bright
    CircuitPlayground.setBrightness(10);

    //
    // Set up callbacks
    //

    // Register taps
    CircuitPlayground.setAccelRange(LIS3DH_RANGE_2_G);
    CircuitPlayground.setAccelTap(2, TAP_THRESHOLD);
    attachInterrupt(digitalPinToInterrupt(7), onTap, FALLING);
}

//
// Loop
//
void loop() {
    uint32_t currentColor = defaultColor;
    unsigned long currentTime = millis();

    /*
    // test Red #13 LED
    pinLevel = !pinLevel;
    CircuitPlayground.redLED(pinLevel);
    */

    isLoggingLoop = false;
    if (currentTime - previousUpdate > interval)
    {
        pixeln++;
        if (pixeln == 11) {
            pixeln = 0;
            CircuitPlayground.clearPixels();
            tapCount = 0;
        }

        previousUpdate = currentTime;
        isLoggingLoop = true;
    }

    /************* TEST CAPTOUCH */
    uint16_t cap10Value = CircuitPlayground.readCap(10);
    if (isLoggingLoop)
    {
        char capStatusMessage[128];
        snprintf(capStatusMessage, 128, "Capsense: %d %d %d %d %d %d %d %d",
            CircuitPlayground.readCap(3), CircuitPlayground.readCap(2), CircuitPlayground.readCap(0), CircuitPlayground.readCap(1),
            CircuitPlayground.readCap(12), CircuitPlayground.readCap(6), CircuitPlayground.readCap(9), cap10Value);
        Serial.println(capStatusMessage);
    }
    //
    // Render state onto LEDs
    //

    // Set tap indicator
    for (uint8_t i = 0; i < tapCount && i < 10; i++)
    {
        CircuitPlayground.setPixelColor(i, TAP_COLOR);
    }

    // Set normal counter
    if (cap10Value < 40)
    {
        for (uint8_t i = tapCount; i < pixeln; i++)
        {
            CircuitPlayground.setPixelColor(i, CircuitPlayground.colorWheel(i * 25));
        }
    }
    else
    {
        for (uint8_t i = pixeln - 1; i >= tapCount; i--)
        {
            unsigned long color = CircuitPlayground.colorWheel(i * 25);
            if (isLoggingLoop)
            {
                char capStatusMessage[128];
                snprintf(capStatusMessage, 128, "[ReverseLoop] i=%d color=%d", i, color);
                Serial.println(capStatusMessage);
            }
            CircuitPlayground.setPixelColor(i, color);
        }
    }
}

void onTap()
{
    Serial.println("Tappy!");
    tapCount++;
}
