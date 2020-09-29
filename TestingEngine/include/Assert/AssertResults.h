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
			if(AssertFailed())
			{
				IO::LogString("Assert Failed:");

				IO::IndentOut();
				LogFailedAssertDetails();
				IO::IndentIn();
			}
			else
			{
				IO::LogString("Assert Succeeded:");

				IO::IndentOut();
				LogAssertType();
				IO::IndentIn();
			}
		}

		void LogFailedAssertDetails() const
		{
			LogAssertType();
			IO::NewLine();

			IO::LogString("Contents:");

			IO::IndentOut();
			LogAssertContents();
			IO::IndentInWithoutNewline();
		}

		void LogAssertType() const
		{
			IO::LogString("Type:");
			IO::IndentOut();
			IO::LogString(GetAssertType());
			IO::IndentInWithoutNewline();
		}

		virtual void LogAssertContents() const = 0;
		virtual std::string GetAssertType() const = 0;
	};

	template<typename AssertType>
	class AssertWithoutMessage : public AssertResult
	{
	protected:
		Optional<AssertType> details;
	public:
		AssertWithoutMessage()
			: details()
		{}

		bool AssertFailed() const override { return details.HasValue(); }

		template<typename ... Ts>
		AssertWithoutMessage(Ts&& ... ts)
			: details(std::forward<Ts>(ts)...)
		{}

		void LogAssertContents() const override
		{
			details->LogDetails();
		}

		std::string GetAssertType() const override final
		{
			return AssertType::Name;
		}
	};

	template<typename AssertType>
	class AssertWithMessage : public AssertWithoutMessage<AssertType>
	{
		std::string ErrorMessage;

		void LogErrorMessage() const
		{
			IO::LogString("Message:");
			IO::IndentOut();
			IO::LogString(ErrorMessage);
			IO::IndentIn();
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
			this->details->LogDetails();
		}
	};

	
}