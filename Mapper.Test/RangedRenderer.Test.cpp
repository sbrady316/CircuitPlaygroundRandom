#include "pch.h"
#include "CppUnitTest.h"
#include "..\Pomodoro\src\RangedRenderer.h"
#include "..\Pomodoro\src\RangedRenderer.cpp"

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

			auto* colors = rr.Render(10 * 1000);
			for (auto i = 0; i < 10; i++)
			{
				Assert::AreEqual(color, colors[i]);
			}
		}
	};
}
