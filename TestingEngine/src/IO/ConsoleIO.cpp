#include "ConsoleIO.h"

#include "IO.h"

namespace Testing
{
	void ConsoleIO:: IndentOut()
	{
		m_Indents++;
		Newline();
	}

	void ConsoleIO::IndentIn()
	{
		IndentInWithoutNewline();
		Newline();
	}

	void ConsoleIO::IndentInWithoutNewline()
	{
		m_Indents--;
	}

	void ConsoleIO::LogIndent() const
	{
		for (unsigned int i = 0; i < m_Indents; i++)
		{
			std::cout << "  "; //Indent is 2 spaces for now
		}
	}

	void ConsoleIO::LogIndent(std::ostream& stream) const
	{
		for (unsigned int i = 0; i < m_Indents; i++)
		{
			stream << "  "; //Indent is 2 spaces for now
		}
	}

	void ConsoleIO::LogSuccess() const
	{
		std::cout << "Test Succeeded!";
	}

	void ConsoleIO::LogFailure() const
	{
		std::cout << "Test Failed!";
	}

	void ConsoleIO::LogString(const std::string& s) const
	{
		std::cout << s;
	}

	void ConsoleIO::Newline() const
	{
		std::cout << '\n';
		LogIndent();
	}

	void ConsoleIO::Newline(std::ostream& stream) const
	{
		stream << '\n';
		LogIndent();
	}

	void ConsoleIO::Flush() const
	{
		std::cout << std::flush;
	}

	void ConsoleIO::Endline() const
	{
		std::cout << std::endl;
		LogIndent();
	}

	void ConsoleIO::LogAssert(const AssertResultAPI& res) const
	{
		res.LogAssert();
	}
}