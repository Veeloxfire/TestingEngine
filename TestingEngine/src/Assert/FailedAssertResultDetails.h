#pragma once
#include <string>
#include "IO\IO.h"

namespace Testing
{
	class FailedAssertDetails
	{
		virtual void LogDetails() const = 0;
		virtual const char* GetAssertType() const = 0;
	};

	template <typename Type>
	class AreEqualDetails : public FailedAssertDetails
	{
		Type Expected;
		Type Actual;
	public:
		AreEqualDetails(const Type& e, const Type& a)
			:Expected(e), Actual(a)
		{}

		const char* GetAssertType() const override {
			static constexpr const char* Name = "AreEqual";
			return Name;
		}

		void LogDetails() const override
		{
			LogExpected();
			LogActual();
		}

		void LogExpected() const
		{
			IO::LogStringAndNewline("Expected:");
			IO::LogObject(Expected);
		}
		void LogActual() const
		{
			IO::LogStringAndNewline("Actual:");
			IO::LogObject(Actual);
		}
	};
}