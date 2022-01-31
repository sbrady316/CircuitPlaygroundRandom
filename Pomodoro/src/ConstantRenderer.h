#pragma once
#include <stdint.h>
#include "IIntervalRenderer.h"

class ConstantRenderer :
    public IIntervalRenderer
{
public:
	// Not sure why size_t can't be found when compiling for arduino...
	ConstantRenderer(unsigned long color, unsigned int colorCount)
	{
		currentView = new unsigned long[colorCount];

		for (auto i = 0; i < colorCount; i++)
		{
			//unsigned long defaultColor = 0;
			//if (i % 2 == 1)
			//{
				currentView[i] = color;
			//}
			//else
			//{
			//	currentView[i] = 0;
			//}
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
	virtual const unsigned long* Render(unsigned long ignored);

private:
	unsigned long * currentView;
};

