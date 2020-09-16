#pragma once
#include "LogObject\LogObject.h"
#include <string>
#include <sstream>
#include <iostream>

namespace Testing
{
	class ConsoleIO
	{
	public:
		void LogSuccess() const;
		void LogFailure() const;
		void LogString(const std::string& s) const;
		void Newline() const;
		void Flush() const;
		void Endline() const;

		template<typename Top, typename ... Types>
		void LogObject(const LogObject<Top, Types...>& log) const
		{
			std::cout << TypeNames::TypeName<Top>::name << ":\n";
			RecursivelyStreamObject(log, std::cout);
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
				stream << '\n';
				RecursivelyStreamObject<Spaces + 1>(log.GetFirst(), stream);
			}
			else
			{
				stream << log.GetFirst() << '\n';
			}

			RecursivelyStreamObject<Spaces>(log.NextObj(), stream);
		}

		template< unsigned int Spaces = 1, typename Top, typename Last>
		void RecursivelyStreamObject(const Testing::LogObject<Top, Last>& log, std::ostream& stream) const
		{
			for (unsigned int i = 0; i < Spaces; i++)
			{
				stream << ' ';
			}

			stream << log.GetFirstName() << ": ";

			if constexpr (IsBaseOf<LogObjectBase, Last>::value)
			{
				stream << '\n';
				RecursivelyStreamObject<Spaces + 1>(log.GetFirst(), stream);
			}
			else
			{
				stream << log.GetFirst() << '\n';
			}
		}
	};
}