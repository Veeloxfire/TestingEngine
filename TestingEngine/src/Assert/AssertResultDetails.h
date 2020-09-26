#pragma once
#include <string>
#include "IO\IO.h"

namespace Testing
{
	template <typename Type>
	class AreEqualDetails
	{
		Type Expected;
		Type Actual;
		
	public:
		constexpr static const char* Name = "AreEqual";

		AreEqualDetails(Type&& e, Type&& a)
			:Expected(std::forward<Type>(e)), Actual(std::forward<Type>(a))
		{}

		void LogDetails() const
		{
			LogExpected();
			LogActual();
		}

	private:
		void LogExpected() const
		{
			IO::LogString("Expected:");

			IO::IndentOut();
			IO::LogObject(Expected);
			IO::IndentIn();
		}
		void LogActual() const
		{
			IO::LogString("Actual:");

			IO::IndentOut();
			IO::LogObject(Actual);
			IO::IndentIn();
		}
	};
}