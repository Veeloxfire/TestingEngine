#pragma once
#include "Utility\Traits.h"

#include "FailedAssertResultAPI.h"
#include "FailedAssertResultDetails.h"

#include "IO\IO.h"
#include <string>

namespace Testing
{
	class FailedAssertResult : public FailedAssertResultAPI
	{
	public:
		void LogFailedAssert() const override final
		{
			LogAssertType();

			IO::LogStringAndNewline("Contents:");
			LogAssertContents();
		}

		void LogAssertType() const
		{
			IO::LogString("Assert Failed Of Type: ");
			IO::LogStringAndNewline(GetAssertType());
		}

		virtual void LogAssertContents() const = 0;
		virtual std::string GetAssertType() const = 0;
	};

	template<typename AssertType>
	class FailedAssertWithoutMessage : public FailedAssertResult
	{
		static_assert(IsBaseOf<FailedAssertDetails, AssertType>::value, "Assert type must implement FailedAssertDetails");

		AssertType details;
	public:
		template<typename ... Ts>
		FailedAssertWithoutMessage(const Ts& ... ts)
			: details(ts...)
		{}

		void LogAssertContents() const override final
		{
			details.LogDetails();
		}

		std::string GetAssertType() const override final
		{
			return details.GetAssertType();
		}
	};

	template<typename AssertType>
	class FailedAssertWithMessage : public FailedAssertResult
	{
		static_assert(IsBaseOf<FailedAssertDetails, AssertType>::value, "Assert type must implement FailedAssertDetails");

		std::string ErrorMessage;
		AssertType details;

		void LogErrorMessage() const
		{
			IO::LogStringAndNewline(ErrorMessage);
		}

	public:
		template<typename ... Ts>
		FailedAssertWithMessage(std::string&& Message, const Ts& ... ts)
			: ErrorMessage(std::move(Message)), details(ts...)
		{}

		void LogAssertContents() const override final
		{
			LogErrorMessage();
			details.LogDetails();
		}

		const std::string& GetAssertType() const override final
		{
			return details.GetAssertType();
		}
	};

	
}