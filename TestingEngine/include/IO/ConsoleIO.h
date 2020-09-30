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
		mutable unsigned int m_Indents = 0;

		void LogIndent() const
		{
			for (unsigned int i = 0; i < m_Indents; i++)
			{
				std::cout << "  "; //Indent is 2 spaces for now
			}
		}

		void LogIndent(std::ostream& stream) const
		{
			for (unsigned int i = 0; i < m_Indents; i++)
			{
				stream << "  "; //Indent is 2 spaces for now
			}
		}
	public:
		void IndentOut() const
		{
			m_Indents++;
			Newline();
		}

		void IndentIn() const
		{
			IndentInWithoutNewline();
			Newline();
		}

		void IndentInWithoutNewline() const
		{
			m_Indents--;
		}

		void LogSuccess() const
		{
			std::cout << "Test Succeeded!";
		}

		void LogFailure() const
		{
			std::cout << "Test Failed!";
		}

		void LogString(const std::string& s) const
		{
			std::cout << s;
		}

		void Newline() const
		{
			std::cout << '\n';
			LogIndent();
		}

		void Newline(std::ostream& stream) const
		{
			stream << '\n';
			LogIndent();
		}

		void Flush() const
		{
			std::cout << std::flush;
		}

		void Endline() const
		{
			std::cout << std::endl;
			LogIndent();
		}

		void LogAssert(const AssertResultAPI& res) const
		{
			res.LogAssert();
		}

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