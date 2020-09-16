#include "IO.h"
#include <utility>

namespace Testing
{
	const IO::API& IO::GetAPI()
	{
		static const API io = {};
		return io;
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