#pragma once

/*
Utilities for the Pomodoro project
*/
#include "src\IIntervalRenderer.h"
#include "src\ConstantRenderer.h"
#include "src\RangedRenderer.h"
#include "src\CompositeRenderer.h"
#include "src\PassThroughLogger.h"

class RenderConfig
{
public:
	RenderConfig(IIntervalRenderer* renderer, unsigned long durationMs, unsigned long currentTimeMs)
		: _renderer(renderer), _endTimeMs(currentTimeMs+durationMs)
	{
	}

    IIntervalRenderer* GetRenderer() { return _renderer; }
    unsigned long GetEndTime() { return _endTimeMs; }

private:
	IIntervalRenderer* _renderer;
	unsigned long _endTimeMs;
};


class SerialLogger : public ILogSink
{
    virtual void Log(const char* message)
    {
        Serial.print(message);
    }
};

enum Colors {
    Red = 0xFF0000,
    Green = 0x00FF00,
    Blue = 0x0000FF,
};

SerialLogger sl;
PassThroughLogger logger(sl);


