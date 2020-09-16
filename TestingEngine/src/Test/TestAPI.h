#pragma once
#include "TestResult.h"

namespace Testing
{
	class TestAPI
	{
	public:
		virtual const char* GetName() const = 0;
		virtual bool RunCode() = 0;
		virtual void TestFunction() = 0;
	};
}