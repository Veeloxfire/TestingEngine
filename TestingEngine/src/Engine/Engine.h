#pragma once
#include "EngineAPI.h"
#include "Assert\FailedAssertResultAPI.h"

namespace Testing
{
	class Engine : public EngineAPI
	{
		bool AllTestsSucceeded = true;

		TestAPI* Tests = nullptr;
		unsigned int NumberOfTests = 0;
	public:
		void SetTests(TestAPI* tests, unsigned int numberOfTests) override;
		void RunAllTests() override;

		void LogTestFailure() override;
		void LogAssertFailure(const FailedAssertResultAPI& result) override;
	private:
		void RunTest(TestAPI& test);
		
		void LogTestStart(const TestAPI& test);
		void LogTestSuccess();
	};
}