#pragma once
#include <string>
#include "IO\IO.h"

namespace Testing
{
	class AssertDetails
	{
	public:
		virtual bool AssertFailed() const = 0;
		virtual void LogDetails() const = 0;
	};

	template <typename Type>
	class AreEqualDetails : public AssertDetails
	{
		Type Expected;
		Type Actual;
		
	public:
		static constexpr char* Name = "AreEqual";

		AreEqualDetails(Type&& e, Type&& a)
			:Expected(std::forward<Type>(e)), Actual(std::forward<Type>(a))
		{}

		bool AssertFailed() const override
		{
			return Result.HasValue();
		}

		const char* GetAssertType() const override {
			static constexpr const char* Name = "AreEqual";
			return Name;
		}

		void LogDetails() const override
		{
			LogExpected();
			LogActual();
		}

	private:
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