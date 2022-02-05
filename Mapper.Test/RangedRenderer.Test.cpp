#include "pch.h"
#include "CppUnitTest.h"
#include "..\Pomodoro\src\RangedRenderer.h"
#include "..\Pomodoro\src\RangedRenderer.cpp"
#include "..\Pomodoro\src\PassThroughLogger.h"
#include "Logging.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MapperTest
{
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

		TEST_METHOD(Render_IsExpected)
		{
			wchar_t reason[128];

			const size_t count = 10;
			unsigned long color = 0x00FF00;
			
			RangedRenderer rr(10 * 1000, color, count);

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
				auto renderBuffer = rr.Render(answer.TimeMs);
				logger.LogArray(tag, renderBuffer, count);
				logger.LogArray("Expected", answer.Colors, count);
				for (auto i = 0; i < count; i++)
				{
					swprintf_s(reason, 128, L"TimeMs = %d, i = %d", answer.TimeMs, i);
					Assert::AreEqual(answer.Colors[i], renderBuffer[i], reason);
				}
			}
		}

		TEST_METHOD(Render_Red)
		{
			wchar_t reason[128];

			const size_t count = 10;
			unsigned long color = 0xFF0000;

			RangedRenderer rr(10 * 1000, color, count);

			RenderAnswer answers[] = {
				RenderAnswer(0, new unsigned long[] {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }),
				RenderAnswer(500, new unsigned long[] {0x7F0000, 0, 0, 0, 0, 0, 0, 0, 0, 0 }),
				RenderAnswer(1500, new unsigned long[] {color, 0x7F0000, 0, 0, 0, 0, 0, 0, 0, 0}),
				RenderAnswer(10 * 1000, new unsigned long[] {color, color, color, color, color, color, color, color, color, color}), // Max value = no fading
				RenderAnswer(10 * 1000 + 1, new unsigned long[] {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }), // Higher than max value == all off
			};

			for (auto answer : answers)
			{
				auto renderBuffer = rr.Render(answer.TimeMs);
				logger.LogArray(answer.TimeMs, renderBuffer, count);
				logger.LogArray("Expected", answer.Colors, count);
				for (auto i = 0; i < count; i++)
				{
					swprintf_s(reason, 128, L"TimeMs = %d, i = %d", answer.TimeMs, i);
					Assert::AreEqual(answer.Colors[i], renderBuffer[i], reason);
				}
			}
		}

		TEST_METHOD(Render_60)
		{
			wchar_t reason[128];

			const size_t count = 10;
			unsigned long color = 0xFF0000;

			RangedRenderer rr(60 * 1000, color, count);

			RenderAnswer answers[] = {
				RenderAnswer(-6000, new unsigned long[] {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }),
				RenderAnswer(0, new unsigned long[] {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }),
				RenderAnswer(3000, new unsigned long[] {0x7F0000, 0, 0, 0, 0, 0, 0, 0, 0, 0 }),
				RenderAnswer(9000, new unsigned long[] {color, 0x7F0000, 0, 0, 0, 0, 0, 0, 0, 0}),
				RenderAnswer(60 * 1000, new unsigned long[] {color, color, color, color, color, color, color, color, color, color}), // Max value = no fading
				RenderAnswer(60 * 1000 + 1, new unsigned long[] {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }), // Higher than max value == all off
			};

			for (auto answer : answers)
			{
				auto renderBuffer = rr.Render(answer.TimeMs);
				logger.LogArray(answer.TimeMs, renderBuffer, count);
				logger.LogArray("Expected", answer.Colors, count);
				for (auto i = 0; i < count; i++)
				{
					swprintf_s(reason, 128, L"TimeMs = %d, i = %d", answer.TimeMs, i);
					Assert::AreEqual(answer.Colors[i], renderBuffer[i], reason);
				}
			}
		}

		TEST_METHOD(GetValue_HappyPath)
		{
			wchar_t reason[128];
			const size_t count = 10;
			unsigned long color = 0xFF0000;

			RangedRenderer rr(60 * 1000, color, count);

			GetValueAnswer answers[] = {
				GetValueAnswer(0, -6000, 0),
				GetValueAnswer(0, 0, 0),
				GetValueAnswer(0, 3000, 0x7F0000),
				GetValueAnswer(1, 3000, 0),
				GetValueAnswer(0, 9000, color),
				GetValueAnswer(1, 9000, 0x7F0000),
				GetValueAnswer(2, 9000, 0),
				GetValueAnswer(count-1, 60 * 1000, color), // Max value = no fading
				GetValueAnswer(0, 60 * 1000 + 1, 0), // Higher than max value == all off
			};

			for (const GetValueAnswer& answer : answers)
			{
				auto actual = rr.GetValue(answer.Position, answer.TimeMs);
				swprintf_s(reason, 128, L"Position = %d, TimeMs = %d", answer.Position, answer.TimeMs);
				Assert::AreEqual(answer.Expected, actual, reason);
			}
		}

		TEST_METHOD(Fade_Test)
		{
			char loggingBuffer1[128], loggingBuffer2[128], loggingBuffer3[128], loggingBuffer4[128];
			const size_t count = 10;
			unsigned long color = 0x00FF00;

			RangedRenderer rr(10 * 1000, color, count);

			Assert::AreEqual(logger.Format(loggingBuffer1, "0x%08lX", 0x007F7F7F), logger.Format(loggingBuffer2, "0x%08lX", rr.Fade(0x00FFFFFF, 0.5)));
			Assert::AreEqual(logger.Format(loggingBuffer3, "0x%08lX", 0x007F0000), logger.Format(loggingBuffer4, "0x%08lX", rr.Fade(0x00FF0000, 0.58f)));
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

		class GetValueAnswer
		{
		public:
			GetValueAnswer(size_t position, unsigned long timeMs, argb_t expected)
				: Position(position), TimeMs(timeMs), Expected(expected)
			{

			}

			unsigned long TimeMs;
			size_t Position;
			argb_t Expected;
		};
	};
}
