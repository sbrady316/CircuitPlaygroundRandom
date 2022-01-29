#include "pch.h"
#include "CppUnitTest.h"
#include "..\Pomodoro\src\PassThroughLogger.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MapperTest
{
	TEST_CLASS(PassThroughLoggerTest)
	{
	public:
		PassThroughLoggerTest()
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
			PassThroughLogger logger(Logger::WriteMessage);

			logger.Log("Hello world");
			logger.Log("Hallo, %s", "world");
		}

		TEST_METHOD(LogArray_HappyPath)
		{
			PassThroughLogger logger(Logger::WriteMessage);
			long numbers[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

			logger.LogArray("Ascending", numbers, sizeof(numbers) / sizeof(numbers[0]));
		}

		void LogDelegate(const char* message)
		{
			Logger::WriteMessage(message);
		}
	};
}
