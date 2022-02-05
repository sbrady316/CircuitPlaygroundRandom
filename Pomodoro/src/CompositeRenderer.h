#pragma once
#include <stdint.h>
#include "IIntervalRenderer.h"
class CompositeRenderer :
    public IIntervalRenderer
{
public:
    CompositeRenderer(IIntervalRenderer** renderers, size_t rendererCount, size_t buckets)
        : _renderers(renderers), _rendererCount(rendererCount), _colorsCount(buckets)
    {
        _renderBuffer = new unsigned long[buckets];
    }

    ~CompositeRenderer()
    {
        delete[] _renderBuffer;
    }

    virtual const unsigned long* Render(unsigned long timeMs)
    {
        memset(_renderBuffer, 0, sizeof(_renderBuffer[0]) * _colorsCount);

        for (size_t i = 0; i < _rendererCount; i++)
        {
            auto* newBuffer = _renderers[i]->Render(timeMs);
            for (size_t j = 0; j < _colorsCount; j++)
            {
                _renderBuffer[j] |= newBuffer[j];
            }
        }

        return _renderBuffer;
    }

    /// <summary>
    /// Computes the value for the specified position
    /// </summary>
    /// <param name="index"></param>
    /// <param name="timeMs"></param>
    /// <returns>Color for the specified position and time</returns>
    virtual const argb_t GetValue(size_t index, unsigned long timeMs)
    {
        argb_t returnValue = 0;

        for (auto i = 0; i < _rendererCount; i++)
        {
            auto r = _renderers[i];
            returnValue |= r->GetValue(index, timeMs);
        }
        return returnValue;
    }

private:
    IIntervalRenderer** _renderers;
    const size_t _rendererCount;
    unsigned long* _renderBuffer;
    const size_t _colorsCount;
};

