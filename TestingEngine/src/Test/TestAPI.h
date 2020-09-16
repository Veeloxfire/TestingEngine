#pragma once
#include "TestResult.h"

namespace Testing
{
	class TestAPI
	{
	public:
		virtual const char* GetName() const = 0;
	};
}