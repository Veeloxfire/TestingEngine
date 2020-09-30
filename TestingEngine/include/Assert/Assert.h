#pragma once
#include "AssertResults.h"

namespace Testing
{
	class Assert
	{
	public:
		template <typename Type>
		constexpr static auto AreEqual(Type Expected, Type Actual)
		{
			return AssertWithoutMessage<AreEqualDetails<Type>>::AssertCheck(std::move(Expected), std::move(Actual));
		}

		template <typename Type>
		constexpr static auto AreEqual(Type Expected, Type Actual, std::string Message)
		{
			return AssertWithMessage<AreEqualDetails<Type>>::AssertCheck(std::move(Message), std::move(Expected), std::move(Actual));
		}

		template <typename Type>
		constexpr static auto AreNotEqual(Type Expected, Type Actual)
		{
			return AssertWithoutMessage<AreNotEqualDetails<Type>>::AssertCheck(std::move(Expected), std::move(Actual));
		}

		template <typename Type>
		constexpr static auto AreNotEqual(Type Expected, Type Actual, std::string Message)
		{
			return AssertWithMessage<AreNotEqualDetails<Type>>::AssertCheck(std::move(Message), std::move(Expected), std::move(Actual));
		}
	};
}