#pragma once
#include "Utility\Traits.h"
#include "Utility\Optional.h"

#include "AssertResultAPI.h"
#include "AssertResultDetails.h"

#include "IO\IO.h"
#include <string>

namespace Testing
{
	class AssertResult : public AssertResultAPI
	{
	public:
		void LogAssert() const override final
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
	class AssertWithoutMessage : public AssertResult
	{
		static_assert(IsBaseOf<AssertDetails, AssertType>::value, "Assert type must implement FailedAssertDetails");

		Optional<AssertType> details;
	public:
		AssertWithoutMessage()
			: details()
		{}

		template<typename ... Ts>
		AssertWithoutMessage(Ts&& ... ts)
			: details(std::forward<Ts>(ts)...)
		{}

		void LogAssertContents() const override
		{
			details.LogDetails();
		}

		std::string GetAssertType() const override final
		{
			return AssertType::name;
		}
	};

	template<typename AssertType>
	class AssertWithMessage : public AssertWithoutMessage<AssertType>
	{
		static_assert(IsBaseOf<AssertDetails, AssertType>::value, "Assert type must implement FailedAssertDetails");

		std::string ErrorMessage;

		void LogErrorMessage() const
		{
			IO::LogStringAndNewline(ErrorMessage);
		}

	public:
		template<typename ... Ts>
		AssertWithMessage(std::string&& Message)
			: ErrorMessage(std::move(Message)), AssertWithoutMessage<AssertType>()
		{}

		template<typename ... Ts>
		AssertWithMessage(std::string&& Message, Ts&& ... ts)
			: ErrorMessage(std::move(Message)), AssertWithoutMessage<AssertType>(std::forward<Ts>(ts)...)
		{}

		void LogAssertContents() const override final
		{
			LogErrorMessage();
			details.LogDetails();
		}
	};

	
}