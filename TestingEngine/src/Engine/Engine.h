#pragma once
#include "Test\Tests.h"
namespace Testing
{
	template<typename ... Test>
	class Engine
	{
		Tests<Test...> m_Tests;
	public:
		constexpr Engine(Test&& ... t) : m_Tests(std::forward<Test>(t)...)
		{}

		constexpr void RunAllTests() const
		{
			RecurseAllTests(m_Tests);
		}

	private:
		template<typename First, typename ... Rest>
		constexpr void RecurseAllTests(const Tests<First, Rest...>& tests) const
		{
			RunTest(tests.GetFirst());
			RecurseAllTests<Rest...>(tests);
		}

		template<typename First>
		constexpr void RecurseAllTests(const Tests<First>& tests) const
		{
			RunTest(tests.GetFirst());
		}

		template<typename TestObj>
		void RunTest(const TestObj& test)
		{
			IO::LogStringAndNewline(test.GetName());
			IO::LogTestResult(test());
		}
	};

	template<typename ... Test>
	Engine(Test&& ... t)->Engine<Test...>;
}