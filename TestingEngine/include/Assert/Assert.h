#pragma once
#include "AssertResults.h"

namespace Testing
{
	class Assert
	{
	public:
		template <typename Type>
		[[nodiscard]] constexpr static auto AreEqual(Type Expected, Type Actual)
		{
			return AssertWithoutMessage<AreEqualDetails<Type>>::AssertCheck(std::move(Expected), std::move(Actual));
		}

		template <typename Type>
		[[nodiscard]] constexpr static auto AreEqual(Type Expected, Type Actual, std::string Message)
		{
			return AssertWithMessage<AreEqualDetails<Type>>::AssertCheck(std::move(Message), std::move(Expected), std::move(Actual));
		}

		template <typename Type>
		[[nodiscard]] constexpr static auto AreNotEqual(Type Expected, Type Actual)
		{
			return AssertWithoutMessage<AreNotEqualDetails<Type>>::AssertCheck(std::move(Expected), std::move(Actual));
		}

		template <typename Type>
		[[nodiscard]] constexpr static auto AreNotEqual(Type Expected, Type Actual, std::string Message)
		{
			return AssertWithMessage<AreNotEqualDetails<Type>>::AssertCheck(std::move(Message), std::move(Expected), std::move(Actual));
		}

		template <typename Expected, typename Actual>
		[[nodiscard]] constexpr static auto AreSameType()
		{
			return AssertWithoutMessage<AreSameTypeDetails<Expected, Actual>>::AssertCheck();
		}

		template <typename Expected, typename Actual>
		[[nodiscard]] constexpr static auto AreSameType(std::string Message)
		{
			return AssertWithoutMessage<AreSameTypeDetails<Expected, Actual>>::AssertCheck(std::move(Message));
		}
	};
}