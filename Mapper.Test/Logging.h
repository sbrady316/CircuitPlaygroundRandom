#pragma once
#include "pch.h"
#include "CppUnitTest.h"
#include "..\Pomodoro\src\PassThroughLogger.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MapperTest
{
	class TestLoggerAdapter : public ILogSink
	{
	public:
		virtual void Log(const char* message)
		{
			Logger::WriteMessage(message);
		}
	};
}
