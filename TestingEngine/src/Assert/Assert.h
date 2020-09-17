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
			if (!(Expected == Actual))//!(... == ...) rather than (... != ...) to test correct operator
			{
				return AssertWithoutMessage<AreEqualDetails<Type>>(std::move(Expected), std::move(Actual));
			}
			else
			{
				return AssertWithoutMessage<AreEqualDetails<Type>>();
			}
		}

		template <typename Type>
		constexpr static auto AreEqual(Type Expected, Type Actual, std::string Message)
		{
			if (!(Expected == Actual))//!(... == ...) rather than (... != ...) to test correct operator
			{
				return AssertWithoutMessage<AreEqualDetails<Type>>(std::move(Message), std::move(Expected), std::move(Actual));
			}
			else
			{
				return AssertWithoutMessage<AreEqualDetails<Type>>();
			}
		}
	};
}