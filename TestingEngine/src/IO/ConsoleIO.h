#pragma once
#include "Assert\AssertResultAPI.h"
#include "LogObject\LogObject.h"
#include "Test\TestResult.h"

#include <string>
#include <sstream>
#include <iostream>

namespace Testing
{
	class ConsoleIO
	{
		unsigned int m_Indents = 0;
		void LogIndent() const;
		void LogIndent(std::ostream& stream) const;
	public:
		void IndentOut();
		void IndentIn();
		void IndentInWithoutNewline();

		void LogSuccess() const;
		void LogFailure() const;
		void LogString(const std::string& s) const;
		void Newline() const;
		void Newline(std::ostream& stream) const;
		void Flush() const;
		void Endline() const;
		void LogAssert(const AssertResultAPI& res) const;

		template<typename Top, typename ... Types>
		void LogObject(const LogObject<Top, Types...>& log) const
		{
			std::cout << TypeNames::TypeName<Top>::name << ':';
			Newline();
			RecursivelyStreamObject(log, std::cout);
		}

		template<typename ... AssertResults>
		void LogTestResult(const TestResult<AssertResults...>& log) const
		{
			RecusivelyLogAsserts(log);
		}

		template<typename First>
		void RecusivelyLogAsserts(const TestResult<First>& log) const
		{
			LogAssert(log.GetFirst());
		}

		template<typename First, typename ... Rest>
		void RecusivelyLogAsserts(const TestResult<First, Rest...>& log) const
		{
			LogAssert(log.GetFirst());
			RecusivelyLogAsserts(static_cast<const TestResult<Rest...>&>(log));
		}

	private:
		template<unsigned int Spaces = 1, typename Top, typename First, typename ... Types>
		void RecursivelyStreamObject(const Testing::LogObject<Top, First, Types...>& log, std::ostream& stream) const
		{
			for (unsigned int i = 0; i < Spaces; i++)
			{
				stream << ' ';
			}

			stream << log.GetFirstName() << ": ";

			if constexpr (IsBaseOf<LogObjectBase, First>::value)
			{
				Newline(stream);
				RecursivelyStreamObject<Spaces + 1>(log.GetFirst(), stream);
			}
			else
			{
				stream << log.GetFirst();
				Newline(stream);
			}

			RecursivelyStreamObject<Spaces>(log.NextObj(), stream);
		}

		template<unsigned int Spaces = 1, typename Top, typename Last>
		void RecursivelyStreamObject(const Testing::LogObject<Top, Last>& log, std::ostream& stream) const
		{
			for (unsigned int i = 0; i < Spaces; i++)
			{
				stream << ' ';
			}

			stream << log.GetFirstName() << ": ";

			if constexpr (IsBaseOf<LogObjectBase, Last>::value)
			{
				Newline(stream);
				RecursivelyStreamObject<Spaces + 1>(log.GetFirst(), stream);
			}
			else
			{
				stream << log.GetFirst();
			}
		}
	};
}