#include "pch.hpp"
#include <utility>

namespace Testing
{
	IO::API& IO::GetMutableAPI()
	{
		static API io = {};
		return io;
	}

	const IO::API& IO::GetAPI()
	{
		return GetMutableAPI();
	}

	void IO::IndentIn()
	{
		GetMutableAPI().IndentIn();
	}

	void IO::IndentInWithoutNewline()
	{
		GetMutableAPI().IndentInWithoutNewline();
	}

	void IO::IndentOut()
	{
		GetMutableAPI().IndentOut();
	}

	void IO::NewLine()
	{
		GetAPI().Newline();
	}

	void IO::LogSuccess()
	{
		GetAPI().LogSuccess();
	}

	void IO::LogFailure()
	{
		GetAPI().LogFailure();
	}

	void IO::LogString(const std::string& s)
	{
		GetAPI().LogString(s);
	}

	void IO::LogStringAndNewline(const std::string& s)
	{
		GetAPI().LogString(s);
		GetAPI().Newline();
	}
}