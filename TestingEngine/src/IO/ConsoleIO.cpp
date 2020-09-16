#include "ConsoleIO.h"

#include "IO.h"

namespace Testing
{
	void ConsoleIO::LogSuccess() const
	{
		std::cout << "Test Succeeded!\n";
	}

	void ConsoleIO::LogFailure() const
	{
		std::cout << "Test Failed!\n";
	}

	void ConsoleIO::LogString(const std::string& s) const
	{
		std::cout << s;
	}

	void ConsoleIO::Newline() const
	{
		std::cout << '\n';
	}

	void ConsoleIO::Flush() const
	{
		std::cout << std::flush;
	}

	void ConsoleIO::Endline() const
	{
		std::cout << std::endl;
	}
}