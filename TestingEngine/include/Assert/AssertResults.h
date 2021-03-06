#pragma once
#include "..\Utility\Traits.h"
#include "..\Utility\Optional.h"

#include "AssertResultAPI.h"
#include "AssertResultDetails.h"

#include "..\IO\IO.h"
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
		constexpr AssertWithoutMessage()
			: details()
		{}

		constexpr AssertWithoutMessage(AssertType&& d)
			: details(std::forward<AssertType>(d))
		{}

		void LogAssertContents() const override
		{
			details->LogDetails();
		}

		[[nodiscard]] bool AssertFailed() const override { return details.HasValue(); }

		[[nodiscard]] std::string GetAssertType() const override final
		{
			return AssertType::Name;
		}

		template<typename ... Ts>
		[[nodiscard]] static constexpr AssertWithoutMessage<AssertType> AssertCheck(Ts&& ... ts)
		{
			if (AssertType::AssertBool(ts...))
			{
				return AssertWithoutMessage<AssertType>();
			}
			else
			{
				return AssertWithoutMessage<AssertType>(AssertType(std::forward<Ts>(ts)...));
			}
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
		constexpr AssertWithMessage(std::string&& Message)
			: ErrorMessage(std::move(Message)), AssertWithoutMessage<AssertType>()
		{}

		constexpr AssertWithMessage(std::string&& Message, AssertType&& d)
			: ErrorMessage(std::move(Message)), AssertWithoutMessage<AssertType>(std::move(d))
		{}

		void LogAssertContents() const override final
		{
			LogErrorMessage();
			this->details->LogDetails();
		}

		template<typename ... Ts>
		[[nodiscard]] static constexpr AssertWithMessage<AssertType> AssertCheck(std::string&& Message, Ts&& ... ts)
		{
			if (AssertType::AssertBool(ts...))
			{
				return AssertWithMessage<AssertType>(std::move(Message));
			}
			else
			{
				return AssertWithMessage<AssertType>(std::move(Message), AssertType(std::forward<Ts>(ts)...));
			}
		}
	};

	
}