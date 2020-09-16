#pragma once
#include "FailedAssertResults.h"
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
										FailedAssertWithoutMessage<AreEqualDetails<Type>> result(std::move(Expected),
																								 std::move(Actual));
										return result;
									}
									else
									{
										FailedAssertWithoutMessage<AreEqualDetails<Type>> result;
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
										FailedAssertWithMessage<AreEqualDetails<Type>> result(std::move(Message),
																							  std::move(Expected),
																							  std::move(Actual));
										return result;
									}
									else
									{
										FailedAssertWithoutMessage<AreEqualDetails<Type>> result;
										return result;
									}
								}
			);
		}
	};
}