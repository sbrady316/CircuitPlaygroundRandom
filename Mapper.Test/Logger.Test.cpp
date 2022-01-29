#include "pch.h"
#include "CppUnitTest.h"
#include "..\Pomodoro\src\PassThroughLogger.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MapperTest
{
	class TestLogSink : public ILogSink
	{
	public:
		virtual void Log(const char* message)
		{
			Logger::WriteMessage("TestLogSink: "); Logger::WriteMessage(message);
			strncpy_s(buffer, message, BufferSize);
		}

		const char* GetBuffer()
		{
			return buffer;
		}

	private:
		static const size_t BufferSize = 129; // larger that PassThroughLogger buffer
		char buffer[BufferSize];
	};

	TEST_CLASS(PassThroughLoggerTest)
	{
	public:
		PassThroughLoggerTest()
			: logSink()
		{
		}
		~PassThroughLoggerTest()
		{
		}

		TEST_CLASS_INITIALIZE(ClassInitialize)
		{
			//Logger::WriteMessage("In Class Initialize");
		}
		TEST_CLASS_CLEANUP(ClassCleanup)
		{
			//Logger::WriteMessage("In Class Cleanup");
		}

		TEST_METHOD(Log_HappyPath)
		{
			PassThroughLogger logger(logSink);

			logger.Log("Hello world");
			logger.Log("Hallo, %s", "world");

			Assert::AreEqual("Hallo, world\n", logSink.GetBuffer());
		}

		TEST_METHOD(LogArray_HappyPath)
		{
			PassThroughLogger logger(logSink);
			long numbers[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

			logger.LogArray("Ascending", numbers, sizeof(numbers) / sizeof(numbers[0]));
		}

	private:
		TestLogSink logSink;
	};
}
