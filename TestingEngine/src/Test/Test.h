#pragma once
#include "TypeNames\Array.h"
#include "Assert\Assert.h"
#include "TestResult.h"

namespace Testing
{
	class TestBase {};

	template<unsigned int NameLength, typename TestFunction>
	class Test : public TestBase
	{
		using ReturnType = ReturnTypeOf<TestFunction>;

		static_assert(IsBaseOf<TestResultBase, ReturnType>::value, "Function Must Return TestResult");

		const TypeNames::Array<char, NameLength> m_TestName;
		const TestFunction m_TestFunction;
	public:
		constexpr Test(const char (&name)[NameLength], const TestFunction test)
			: m_TestName{ TypeNames::ArrayFactory::Make(name) }, m_TestFunction{test}
		{}

		constexpr const char* GetName() const { return m_TestName.Arr; }
		constexpr ReturnType operator()() const
		{
			return m_TestFunction();
		}
	};

	template<unsigned int NameLength, typename T>
	Test(const char(&name)[NameLength], const T t)->Test<NameLength, T>;
}