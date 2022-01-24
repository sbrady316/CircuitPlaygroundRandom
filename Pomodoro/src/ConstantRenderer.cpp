#include "ConstantRenderer.h"

/// <summary>
/// Renders the value into an array of color values
/// </summary>
/// <param name="toRender">The value to render</param>
/// <returns>Read-only reference to vector</returns>
const led_array & ConstantRenderer::Render(long toRender)
{
	return this->currentView;
}
