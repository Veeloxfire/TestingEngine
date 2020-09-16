#pragma once
#include "TestAPI.h"
#include "Assert\Assert.h"

namespace Testing
{
	class Test : public TestAPI
	{
	protected:
		Assert Assert;

	public:
		Test(EngineAPI& api) : Assert(api) {}
		bool RunCode() override;
	};
}