#pragma once
#include "Test\TestAPI.h"
#include "Assert\FailedAssertResultAPI.h"
namespace Testing
{
	class EngineAPI
	{
	public:
		virtual void SetTests(TestAPI* tests, unsigned int numberOfTests) = 0;
		virtual void RunAllTests() = 0;
		virtual void LogTestFailure() = 0;
		virtual void LogAssertFailure(const FailedAssertResultAPI& result) = 0;
	};
}