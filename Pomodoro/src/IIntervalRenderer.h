#pragma once

typedef uint32_t argb_color_t;

/// <summary>
/// Interface for rendering an integer value (usually time remaining) into a vector of colors
/// </summary>
class IIntervalRenderer
{
public:
	/// <summary>
	/// Renders the value into an array of color values
	/// </summary>
	/// <param name="TimeMs">The value to render</param>
	/// <returns>Read-only reference to vector</returns>
	virtual const unsigned long * Render(unsigned long timeMs) = 0;
};