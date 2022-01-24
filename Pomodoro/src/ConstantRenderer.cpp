#include "ConstantRenderer.h"

const led_array & ConstantRenderer::Render(unsigned long ignored)
{
	return this->currentView;
}
