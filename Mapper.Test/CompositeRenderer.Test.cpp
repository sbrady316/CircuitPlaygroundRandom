#include "pch.h"
#include "CppUnitTest.h"
#include "..\Pomodoro\src\CompositeRenderer.h"
#include "..\Pomodoro\src\ConstantRenderer.cpp"
#include "..\Pomodoro\src\PassThroughLogger.h"
#include "Logging.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MapperTest
{
	TEST_CLASS(CompositeRendererTest)
	{
	private:
		TestLoggerAdapter loggerAdapter;
		PassThroughLogger logger;

	public:
		CompositeRendererTest()
			: logger(loggerAdapter)
		{
		}
		~CompositeRendererTest()
		{
		}

		TEST_METHOD(Render_HappyPath)
		{
			const size_t ledCount = 3;

			ConstantRenderer cr1(0x000000FF, ledCount);
			ConstantRenderer cr2(0x00FF0000, ledCount);

			IIntervalRenderer * childRenderers[] = {&cr1, &cr2};

			CompositeRenderer cr(
				childRenderers,
				2,
				ledCount);

			auto colors = cr.Render(1000);

			logger.LogArray("Composite", colors, ledCount);
		}
	};
}