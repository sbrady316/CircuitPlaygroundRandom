#include "pch.h"
#include "CppUnitTest.h"
#include "..\Pomodoro\src\RangedRenderer.h"
#include "..\Pomodoro\src\RangedRenderer.cpp"
#include "..\Pomodoro\src\PassThroughLogger.h"
#include "Logging.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MapperTest
{
	TEST_MODULE_INITIALIZE(ModuleInitialize)
	{
		//Logger::WriteMessage("In Module Initialize");
	}

	TEST_MODULE_CLEANUP(ModuleCleanup)
	{
		//Logger::WriteMessage("In Module Cleanup");
	}

	TEST_CLASS(RangedRendererTest)
	{
	private:
		TestLoggerAdapter loggerAdapter;
		PassThroughLogger logger;

	public:
		RangedRendererTest()
			: logger(loggerAdapter)
		{
		}
		~RangedRendererTest()
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

		TEST_METHOD(Render_IsExpected)
		{
			wchar_t reason[128];

			const size_t count = 10;
			unsigned long colors[count]{};
			unsigned long color = 0x00FF00;
			
			RangedRenderer rr(10 * 1000, color, colors, count);

			RenderAnswer answers[] = {
				RenderAnswer(0, new unsigned long[] {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }),
				RenderAnswer(500, new unsigned long[] {0x007F00, 0, 0, 0, 0, 0, 0, 0, 0, 0 }),
				RenderAnswer(1500, new unsigned long[] {color, 0x007F00, 0, 0, 0, 0, 0, 0, 0, 0}),
				RenderAnswer(10 * 1000, new unsigned long[] {color, color, color, color, color, color, color, color, color, color}), // Max value = no fading
				RenderAnswer(10 * 1000 + 1, new unsigned long[] {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }), // Higher than max value == all off
			};

			for (auto answer : answers)
			{
				char tag[20];
				sprintf_s(tag, sizeof(tag), "%8d", answer.TimeMs);
				rr.Render(answer.TimeMs);
				logger.LogArray(tag, colors, count);
				logger.LogArray("Expected", answer.Colors, count);
				for (auto i = 0; i < count; i++)
				{
					swprintf_s(reason, 128, L"TimeMs = %d, i = %d", answer.TimeMs, i);
					Assert::AreEqual(answer.Colors[i], colors[i], reason);
				}
			}
		}

		TEST_METHOD(Render_Red)
		{
			wchar_t reason[128];

			const size_t count = 10;
			unsigned long colors[count]{};
			unsigned long color = 0xFF0000;

			RangedRenderer rr(10 * 1000, color, colors, count);

			RenderAnswer answers[] = {
				RenderAnswer(0, new unsigned long[] {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }),
				RenderAnswer(500, new unsigned long[] {0x7F0000, 0, 0, 0, 0, 0, 0, 0, 0, 0 }),
				RenderAnswer(1500, new unsigned long[] {color, 0x7F0000, 0, 0, 0, 0, 0, 0, 0, 0}),
				RenderAnswer(10 * 1000, new unsigned long[] {color, color, color, color, color, color, color, color, color, color}), // Max value = no fading
				RenderAnswer(10 * 1000 + 1, new unsigned long[] {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }), // Higher than max value == all off
			};

			for (auto answer : answers)
			{
				rr.Render(answer.TimeMs);
				logger.LogArray(answer.TimeMs, colors, count);
				logger.LogArray("Expected", answer.Colors, count);
				for (auto i = 0; i < count; i++)
				{
					swprintf_s(reason, 128, L"TimeMs = %d, i = %d", answer.TimeMs, i);
					Assert::AreEqual(answer.Colors[i], colors[i], reason);
				}
			}
		}

		TEST_METHOD(Fade_Test)
		{
			char loggingBufer1[128], loggingBufer2[128], loggingBufer3[128], loggingBufer4[128];
			const size_t count = 10;
			unsigned long colors[count]{};
			unsigned long color = 0x00FF00;

			RangedRenderer rr(10 * 1000, color, colors, count);

			Assert::AreEqual(logger.Format(loggingBufer1, "0x%08lX", 0x007F7F7F), logger.Format(loggingBufer2, "0x%08lX", rr.Fade(0x00FFFFFF, 0.5)));
			Assert::AreEqual(logger.Format(loggingBufer3, "0x%08lX", 0x007F0000), logger.Format(loggingBufer4, "0x%08lX", rr.Fade(0x00FF0000, 0.58)));
		}

		class RenderAnswer
		{
		public:
			RenderAnswer(unsigned long timeMs, unsigned long * colors)
				: TimeMs(timeMs), Colors(colors)
			{}

			unsigned long TimeMs;
			unsigned long * Colors;
		};
	};
}
