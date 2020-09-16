#pragma once

namespace Testing
{
	class TestResultAPI
	{
	public:
		virtual bool DidSucceed() const = 0;
		virtual void GetFailedChecks() const = 0;
	};
}