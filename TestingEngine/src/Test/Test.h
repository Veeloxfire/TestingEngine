#pragma once
#include "TestAPI.h"
#include "Assert\Assert.h"

namespace Testing
{
	template<typename T>
	class Test;

	template<typename ReturnType>
	class Test<ReturnType(*)()> : public TestAPI
	{
		using FunctionType = ReturnType(*)();

		const char* const TestName;
		const FunctionType TestFunction;
	public:
		Test(const char* name, const FunctionType test) : TestName(name) TestFunction(test) {}

		const char* GetName() const { return TestName; }
		ReturnType operator()() const
		{
			return TestFunction();
		}
	};

	template<typename T>
	Test(const T t)->Test<T>;
}