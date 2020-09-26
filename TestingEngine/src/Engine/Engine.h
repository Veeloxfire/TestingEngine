#pragma once
#include "Module\Modules.h"
namespace Testing
{
	template<typename ... Module>
	class Engine
	{
		Modules<Module...> m_Modules;
	public:
		constexpr Engine(Module&& ... m) : m_Modules(std::forward<Module>(m)...)
		{}

		constexpr void RunAllModules() const
		{
			RecurseAllModules(m_Modules);
		}

	private:
		template<typename First, typename ... Rest>
		static constexpr void RecurseAllModules(const Modules<First, Rest...>& modules)
		{
			RunModule(modules.GetFirst());
			RecurseAllModules<Rest...>(modules);
		}

		template<typename First>
		static constexpr void RecurseAllModules(const Modules<First>& modules)
		{
			RunModule(modules.GetFirst());
		}

		template<typename Mod>
		static constexpr void RunModule(const Mod& m)
		{
			IO::LogString(m.GetName());

			IO::IndentOut();
			RecurseAllTests(m.GetTests());
			IO::IndentIn();
		}

		template<typename First, typename ... Rest>
		static constexpr void RecurseAllTests(const Tests<First, Rest...>& tests)
		{
			RunTest(tests.GetFirst());
			RecurseAllTests<Rest...>(tests);
		}

		template<typename First>
		static constexpr void RecurseAllTests(const Tests<First>& tests)
		{
			RunTest(tests.GetFirst());
		}

		template<typename TestObj>
		static constexpr void RunTest(const TestObj& test)
		{
			IO::LogString(test.GetName());
			IO::LogString(" - ");
			AnalyseResult(test());
		}

		template<typename TestResult>
		static constexpr void AnalyseResult(const TestResult& test)
		{
			if (test.Failed())
			{
				IO::LogFailure();

				IO::IndentOut();
				IO::LogTestResult(test);
				IO::IndentIn();
			}
			else
			{
				IO::LogSuccess();
			}
		}

	};

	template<typename ... Module>
	Engine(Module&& ... m)->Engine<Module...>;
}