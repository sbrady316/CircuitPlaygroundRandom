#pragma once
#include <stdint.h>

/// <summary>
/// Type for storing color value as a single 32-bit value as alpha-red-green-blue
/// </summary>
typedef uint32_t argb_t;

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
	//virtual const unsigned long * Render(unsigned long timeMs) = 0;

	/// <summary>
	/// Computes the value for the specified position
	/// </summary>
	/// <param name="index">Position to be rendered</param>
	/// <param name="timeMs">Time remaining in millisecond</param>
	/// <returns>Color for the specified position and time</returns>
	virtual const argb_t GetValue(size_t index, unsigned long timeMs) = 0;
};