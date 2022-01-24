#pragma once
#include "IIntervalRenderer.h"

class ConstantRenderer :
    public IIntervalRenderer
{
public:
	ConstantRenderer()
		: currentView()
	{
		for (auto i = 0; i < sizeof(currentView); i++)
		{
			long color = 0;
			if (i % 2 == 1)
			{
				color = this->DefaultColor;
			}

			this->currentView[i] = color;
		}
	}

	/// <summary>
	/// Renders the value into an array of color values
	/// </summary>
	/// <param name="ignored">Time to render.  Ignored in this implementation.</param>
	/// <returns>Read-only reference to vector</returns>
	const virtual led_array & Render(unsigned long ignored);

private:
	led_array currentView;
	const long DefaultColor = 0x00FF00;
};

