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
	/// <param name="color">Color used by this renderer</param>
	/// <param name="count">Size of buffer</param>
	RangedRenderer(unsigned long maxTimeMs, uint32_t color, size_t count)
		: _maxTimeMs(maxTimeMs), _color(color), _count(count)
	{
		_colors = new unsigned long[count];
	}

	~RangedRenderer()
	{
		delete[] _colors;
	}
		

	/// <summary>
	/// Renders the value into an array of _color values
	/// </summary>
	/// <param name="TimeMs">The value to render</param>
	/// <returns>Read-only pointer to array of values</returns>
	//virtual const unsigned long * Render(unsigned long timeMs);

	/// <summary>
	/// Computes the value for the specified position
	/// </summary>
	/// <param name="index"></param>
	/// <param name="timeMs"></param>
	/// <returns>Color for the specified position and time</returns>
	virtual const argb_t GetValue(size_t index, unsigned long timeMs)
	{
		argb_t value = 0;

		// All "off" for times outside the range
		if (timeMs > _maxTimeMs)
		{
			value = 0;
		}
		else
		{
			float unitsRemaining = ((float)timeMs / _maxTimeMs) * _count;
			size_t wholeUnits = static_cast<uint8_t>(unitsRemaining);
			float fractionalUnits = unitsRemaining - wholeUnits;

			if (index < wholeUnits)
			{
				value = _color;
			}
			else if (index == wholeUnits)
			{
				value = Fade(_color, fractionalUnits);
			}
			else
			{
				value = 0x00000000;
			}
		}

		return value;
	}

	/// <summary>
	/// Fades a _color in its component parts by the specified ratio, e.g. 0.5 would reduce intensity by half
	/// </summary>
	/// <param name="_color">Color in ARGB format</param>
	/// <param name="ratio">Ratio by which to reduce intensity</param>
	/// <returns></returns>
	unsigned long Fade(unsigned long color, float ratio);

private:
	const unsigned long _maxTimeMs;
	const uint32_t _color;
	unsigned long* _colors;
	const size_t _count;
};