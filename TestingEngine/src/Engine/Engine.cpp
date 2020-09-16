#include "Engine.h"
#include "IO\IO.h"

namespace Testing
{
	void Engine::SetTests(TestAPI* tests, unsigned int numberOfTests)
	{
		Tests = tests;
		NumberOfTests = numberOfTests;
	}

	void Engine::RunAllTests()
	{
		AllTestsSucceeded = true;
		for (unsigned int i = 0; i < NumberOfTests; i++)
		{
			RunTest(Tests[i]);
		}
	}

	void Engine::LogAssertFailure(const FailedAssertResultAPI& result)
	{
		result.LogFailedAssert();
	}

	void Engine::RunTest(TestAPI& test)
	{
		LogTestStart(test);

		bool TestFailed = test.RunCode();

		if (!TestFailed)
		{
			LogTestSuccess();
		}
	}

	void Engine::LogTestStart(const TestAPI& test)
	{
		IO::LogString(test.GetName());
		IO::LogString(" - ");
	}

	void Engine::LogTestSuccess()
	{
		IO::LogSuccess();
	}

	void Engine::LogTestFailure()
	{
		IO::LogFailure();
	}
}