#pragma once

namespace Testing
{
	class AssertResultAPI
	{
	public:
		virtual bool AssertFailed() const = 0;
		virtual void LogAssert() const = 0;
	};
}