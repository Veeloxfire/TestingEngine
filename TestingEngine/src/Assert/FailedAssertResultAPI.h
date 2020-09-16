#pragma once

namespace Testing
{
	class FailedAssertResultAPI
	{
	public:
		virtual void LogFailedAssert() const = 0;
	};
}