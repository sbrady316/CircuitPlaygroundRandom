// Implementation for Ranged renderer
// 
// 
#include <string.h>
#include <math.h>
#include "RangedRenderer.h"


    /// <summary>
    /// Renders the value into an array of color values
    /// </summary>
    /// <param name="timeMs">The value to render</param>
    /// <returns>Read-only reference to vector</returns>
const unsigned long * RangedRenderer::Render(unsigned long timeMs)
{
    // All "off" for times outside the range
    if (timeMs > this->maxTimeMs)
    {
        memset(this->currentView, 0, sizeof(this->currentView));
    }
    else
    {
        float unitsRemaining = ((float)timeMs / this->maxTimeMs) * this->ledCount;
        uint8_t wholeUnits = static_cast<uint8_t>(floor(unitsRemaining));

        // Fade the "last" led by reducing its color by the fractional unit remaining
        // This goes before the whole units to cover the case where wholeUnits == unitsRemaining
        this->currentView[wholeUnits] = static_cast<long>(this->color * (unitsRemaining - wholeUnits));

        // Set whole units to the full color specified by the caller
        for (uint8_t i = 0; i < wholeUnits; i++)
        {
            currentView[i] = color;
        }
    }

    return this->currentView;
}