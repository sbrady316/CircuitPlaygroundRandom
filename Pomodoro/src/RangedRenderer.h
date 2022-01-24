#pragma once
#include <stdint.h>
#include "IIntervalRenderer.h"

/// <summary>
/// Implements a renderer that accepts a range of time it needs to map to the led array 
/// </summary>
class RangedRenderer :
	public IIntervalRenderer
{
public:
	/// <summary>
	/// Initializes a new instance with the specified max value
	/// </summary>
	/// <param name="maxTimeMs">The maximum value to be rendered</param>
	RangedRenderer(unsigned long maxTimeMs, uint32_t color)
		: currentView(), maxTimeMs(maxTimeMs), color(color)
	{
	}

	/// <summary>
	/// Renders the value into an array of color values
	/// </summary>
	/// <param name="timeMs">The value to render</param>
	/// <returns>Read-only reference to vector</returns>
	const virtual led_array& Render(unsigned long timeMs);

private:
	led_array currentView;
	const unsigned long maxTimeMs;
	const uint32_t color;

	// Probably need to pass in the number of LEDs in the constructor
	const uint8_t ledCount = sizeof currentView / sizeof currentView[0];
};