#pragma once

/// <summary>
/// Array for managing LED state.
/// TODO:  Make this dynamic
/// </summary>
typedef long led_array[10];

/// <summary>
/// Interface for rendering an integer value (usually time remaining) into a vector of colors
/// </summary>
class IIntervalRenderer
{
public:
	/// <summary>
	/// Renders the value into an array of color values
	/// </summary>
	/// <param name="timeMs">The value to render</param>
	/// <returns>Read-only reference to vector</returns>
	const virtual led_array & Render(unsigned long timeMs) = 0;
};