#pragma once
#include "AssertResults.h"
#include "AssertLambda.h"

namespace Testing
{
	class Assert
	{
	public:
		template <typename Type>
		constexpr static auto AreEqual(Type Expected, Type Actual)
		{
			return AssertLambda([&]()
								{
									if (!(Expected == Actual))//!(... == ...) rather than (... != ...) to test correct operator
									{
										AssertWithoutMessage<AreEqualDetails<Type>> result(std::move(Expected),
																						   std::move(Actual));
										return result;
									}
									else
									{
										AssertWithoutMessage<AreEqualDetails<Type>> result;
										return result;
									}
								}
			);
		}

		template <typename Type>
		constexpr static auto AreEqual(Type Expected, Type Actual, std::string Message)
		{
			return AssertLambda([&]()
								{
									if (!(Expected == Actual))//!(... == ...) rather than (... != ...) to test correct operator
									{
										AssertWithMessage<AreEqualDetails<Type>> result(std::move(Message),
																						std::move(Expected),
																						std::move(Actual));
										return result;
									}
									else
									{
										AssertWithoutMessage<AreEqualDetails<Type>> result;
										return result;
									}
								}
			);
		}
	};
}