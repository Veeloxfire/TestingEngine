#pragma once
#include "TestResultAPI.h"

namespace Testing
{
	class TestResult : public TestResultAPI
	{

	public:
		bool DidSucceed() const override;
		void GetFailedChecks() const override;
	};
}