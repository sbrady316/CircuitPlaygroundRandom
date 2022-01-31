#pragma once
#include <stdint.h>
#include "IIntervalRenderer.h"
class CompositeRenderer :
    public IIntervalRenderer
{
public:
    CompositeRenderer(IIntervalRenderer** renderers, size_t rendererCount, unsigned long* colors, size_t colorsCount)
        : _renderers(renderers), _rendererCount(rendererCount), _colors(colors), _colorsCount(colorsCount)
    {
    }

    virtual const unsigned long* Render(unsigned long timeMs)
    {
        memset(_colors, 0, sizeof(_colors[0]) * _colorsCount);

        for (auto i = 0; i < _rendererCount; i++)
        {
            auto* newBuffer = _renderers[i]->Render(timeMs);
            for (auto j = 0; j < _colorsCount; j++)
            {
                _colors[j] |= newBuffer[j];
            }
        }

        return _colors;
    }

private:
    IIntervalRenderer** _renderers;
    const size_t _rendererCount;
    unsigned long* _colors;
    const size_t _colorsCount;
};

