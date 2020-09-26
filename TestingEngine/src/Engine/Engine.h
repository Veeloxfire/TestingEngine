#pragma once
#include "Test\Tests.h"
namespace Testing
{
	template<typename ... Modules>
	class Engine
	{
		Tests<Test...> m_Tests;
	public:
		constexpr Engine([[maybe_unused]] int dummy, Test&& ... t) : m_Tests(std::forward<Test>(t)...)
		{}

		constexpr Engine(Test&& ... t) : m_Tests(std::forward<Test>(t)...)
		{}

		constexpr Engine(Tests<Test...>&& t) : m_Tests(std::move(t))
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
		void RunTest(const TestObj& test) const
		{
			IO::LogString(test.GetName());
			IO::LogString(" - ");
			AnalyseResult(test());
		}

		template<typename TestResult>
		void AnalyseResult(const TestResult& test) const
		{
			if (test.Failed())
			{
				IO::LogFailure();
				IO::LogTestResult(test);
			}
			else
			{
				IO::LogSuccess();
			}
		}

	};

	template<typename ... Test>
	Engine(Test&& ... t)->Engine<Test...>;

	template<typename ... Test>
	Engine(Tests<Test...>&& t)->Engine<Test...>;

	template<typename ... Test>
	Engine(int dummy, Test&& ... t)->Engine<Test...>;

#define TESTS_START int main() { ::Testing::Engine _engine(0
#define TESTS_END ); _engine.RunAllTests(); }
}