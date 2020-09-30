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
		static const IO::API& GetAPI()
		{
			static const API io = {};
			return io;
		}
	public:
		static void IndentIn()
		{
			GetAPI().IndentIn();
		}

		static void IndentInWithoutNewline()
		{
			GetAPI().IndentInWithoutNewline();
		}

		static void IndentOut()
		{
			GetAPI().IndentOut();
		}
		static void NewLine()
		{
			GetAPI().Newline();
		}

		static void LogSuccess()
		{
			GetAPI().LogSuccess();
		}

		static void LogFailure()
		{
			GetAPI().LogFailure();
		}

		static void LogString(const std::string& s)
		{
			GetAPI().LogString(s);
		}

		static void LogStringAndNewline(const std::string& s)
		{
			GetAPI().LogString(s);
			GetAPI().Newline();
		}

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