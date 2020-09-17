#pragma once
#include "AssertResults.h"
#include "AssertLambda.h"

namespace Testing
{
	class Assert
	{
	public:
		template <typename Type>
		constexpr static auto AreEqual(const Type& Expected, const Type& Actual)
		{
			return AssertLambda([=]()
								{
									if (!(Expected == Actual))//!(... == ...) rather than (... != ...) to test correct operator
									{
										Type E = Expected;
										Type A = Actual;
										AssertWithoutMessage<AreEqualDetails<Type>> result(std::move(E), std::move(A));
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
		constexpr static auto AreEqual(const Type& Expected, const Type& Actual, std::string Message)
		{
			return AssertLambda([=]()
								{
									if (!(Expected == Actual))//!(... == ...) rather than (... != ...) to test correct operator
									{
										Type E = Expected;
										Type A = Actual;
										AssertWithMessage<AreEqualDetails<Type>> result(Message, std::move(E), std::move(A));
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