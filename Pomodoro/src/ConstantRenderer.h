#pragma once
#include <stddef.h>
#include "IIntervalRenderer.h"

class ConstantRenderer :
    public IIntervalRenderer
{
public:
	// Not sure why size_t can't be found when compiling for arduino...
	ConstantRenderer(unsigned long color, size_t colorCount)
		: _color(color)
	{
		currentView = new unsigned long[colorCount];

		for (size_t i = 0; i < colorCount; i++)
		{
			currentView[i] = color;
		}
	}

	~ConstantRenderer()
	{
		delete[] currentView;
	}

	/// <summary>
	/// Renders the value into an array of _color values
	/// </summary>
	/// <param name="ignored">Time to render.  Ignored in this implementation.</param>
	/// <returns>Read-only reference to vector</returns>
	//virtual const unsigned long* Render(unsigned long ignored);

	/// <summary>
	/// Computes the value for the specified position
	/// </summary>
	/// <param name="index">Ignored</param>
	/// <param name="timeMs">Ignored</param>
	/// <returns>Color for the specified position and time</returns>
	virtual const argb_t GetValue(size_t index, unsigned long timeMs)
	{
		return _color;
	}


private:
	argb_t _color;
	unsigned long * currentView;
};

