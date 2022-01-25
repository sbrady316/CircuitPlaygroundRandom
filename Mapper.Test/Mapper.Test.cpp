#include "pch.h"
#include "CppUnitTest.h"
#include "..\Pomodoro\src\RangedRenderer.h"
#include "..\Pomodoro\src\RangedRenderer.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MapperTest
{
	BEGIN_TEST_MODULE_ATTRIBUTE()
		TEST_MODULE_ATTRIBUTE(L"Date", L"2010/6/12")
	END_TEST_MODULE_ATTRIBUTE()


	TEST_MODULE_INITIALIZE(ModuleInitialize)
	{
		Logger::WriteMessage("In Module Initialize");
	}

	TEST_MODULE_CLEANUP(ModuleCleanup)
	{
		Logger::WriteMessage("In Module Cleanup");
	}



	TEST_CLASS(RangedRendererTest)
	{
	public:
		RangedRendererTest()
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
			unsigned long color = 0x00FF00;

			RangedRenderer rr(10 * 1000, color);

			auto& colors = rr.Render(5500);
			unsigned long c0 = colors[0];

			Assert::AreEqual(c0, color);
		}

		TEST_METHOD(Method2)
		{
			Assert::Fail(L"Flagrant error");
		}
	};
}
