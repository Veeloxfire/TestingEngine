#pragma once
#include "ConsoleIO.h"
#include "LogObject\LogObjectFactory.h"

#include <string>

namespace Testing
{
	class IO
	{
	public:
		using API = ConsoleIO;
	private:
		static const API& GetAPI();
	public:
		static void LogSuccess();
		static void LogFailure();
		static void LogString(const std::string& s);
		static void LogStringAndNewline(const std::string& s);

		template<typename Type>
		static void LogObject(const Type& t)
		{
			GetAPI().LogObject(LogObjectFactory<Type>::Build(t));
		}

		template<typename Type>
		static void LogTestResult(const Type& t)
		{
			GetAPI().LogTestResult(t);
		}
	};
}