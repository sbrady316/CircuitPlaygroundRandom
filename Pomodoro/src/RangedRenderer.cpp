// Implementation for Ranged renderer
// 
// 
#include <string.h>
#include <math.h>
#include "RangedRenderer.h"


    /// <summary>
    /// Renders the value into an array of color values
    /// </summary>
    /// <param name="TimeMs">The value to render</param>
    /// <returns>Read-only reference to vector</returns>
const unsigned long * RangedRenderer::Render(unsigned long timeMs)
{
    // All "off" for times outside the range
    if (timeMs > _maxTimeMs)
    {
        memset(_colors, 0, sizeof(_colors[0])*_count);
    }
    else
    {
        float unitsRemaining = ((float)timeMs / _maxTimeMs) * _count;
        size_t wholeUnits = static_cast<uint8_t>(unitsRemaining);
        float fractionalUnits = unitsRemaining - wholeUnits;

        // Set whole units to the full color specified by the caller
        for (auto i = 0; i < wholeUnits; i++)
        {
            _colors[i] = _color;
        }

        // Fade the "last" led by reducing its color by the fractional unit remaining
        // This goes before the whole units to cover the case where wholeUnits == unitsRemaining
        // Need to wrap with the if to handle the case where TimeMs == _maxTimeMs
        if (wholeUnits < _count)
        {
            _colors[wholeUnits] = Fade(_color, fractionalUnits);
        }

        // Set remaining units to off
        for (auto i = wholeUnits+1; i < _count; i++)
        {
            _colors[i] = 0x00000000;
        }
    }

    return _colors;
}

unsigned long RangedRenderer::Fade(unsigned long color, float ratio)
{
    // Compute 2 bytes at a time, using masking to eliminate bleeding between _colors
    const uint32_t a = ((uint32_t)((color & 0xFF000000) * ratio)) & 0xFF000000;
    const uint32_t r = ((uint32_t)((color & 0x00FF0000) * ratio)) & 0x00FF0000;
    const uint32_t g = ((uint32_t)((color & 0x0000FF00) * ratio)) & 0x0000FF00;
    const uint32_t b = ((uint32_t)((color & 0x000000FF) * ratio)) & 0x000000FF;
    const unsigned long output = a | r | g | b;

    return output;
}