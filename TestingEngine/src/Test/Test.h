#pragma once

#include "Assert\Assert.h"
#include "TestResult.h"
namespace Testing
{
	class TestBase {};

	template<typename TestFunction>
	class Test : public TestBase
	{
		using ReturnType = ReturnTypeOf<TestFunction>;

		static_assert(IsBaseOf<TestResultBase, ReturnType>::value, "Function Must Return TestResult");

		const char* const m_TestName;
		const TestFunction m_TestFunction;
	public: 
		constexpr Test(const char* const name, const TestFunction test) : m_TestName(name), m_TestFunction(test) {}

		const char* GetName() const { return m_TestName; }
		ReturnType operator()() const
		{
			return m_TestFunction();
		}
	};

#define TEST_START(name) , ::Testing::Test(name, []()
#define TEST_END )

	template<typename T>
	Test(const char* const name, const T t)->Test<T>;
}