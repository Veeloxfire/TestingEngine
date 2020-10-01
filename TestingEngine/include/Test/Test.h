#pragma once
#include "../TypeNames/Array.h"
#include "../Assert/Assert.h"
#include "../Assert/AssertHelpers.hpp"
#include "TestResult.h"

namespace Testing
{
	class TestBase {};

	template<typename TestFunction>
	concept ReturnsTestResult = requires(TestFunction t, AssertHelpers::ToyClass r, AssertHelpers::ToyClass l)
	{
		{t(std::move(r), l)}->BaseOf<TestResultBase>;
	};

	template<unsigned int NameLength, typename TestFunction> requires ReturnsTestResult<TestFunction>
	class Test : public TestBase
	{
		const TypeNames::Array<char, NameLength> m_TestName;
		const TestFunction m_TestFunction;
	public:
		constexpr Test(const char (&name)[NameLength], const TestFunction test)
			: m_TestName{ TypeNames::ArrayFactory::Make(name) }, m_TestFunction{test}
		{}

		constexpr const char* GetName() const { return m_TestName.Arr; }
		constexpr auto operator()() const
		{
			AssertHelpers::ToyClass rval{};
			AssertHelpers::ToyClass lval{};
			return m_TestFunction(std::move(rval), lval);
		}
	};

	template<unsigned int NameLength, typename T>
	Test(const char(&name)[NameLength], const T t)->Test<NameLength, T>;


	template<typename T>
	concept IsTest = IsBaseOf<TestBase, T>::value;
}