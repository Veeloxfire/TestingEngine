#pragma once
#include "FailedAssertResults.h"
#include "Engine\EngineAPI.h"

namespace Testing
{
	class Assert
	{
		bool Failed = false;
		EngineAPI& Engine;

		void FailAssert(const FailedAssertResultAPI& result)
		{
			if (!HasFailed())
			{
				FailTest();
			}

			Engine.LogAssertFailure(result);
		}

		void FailTest()
		{
			Failed = true;
			Engine.LogTestFailure();
		}

	public:
		Assert(EngineAPI& api) : Engine(api)
		{}

		bool HasFailed() const { return Failed; }

		template <typename Type>
		void AreEqual(const Type& Expected, const Type& Actual)
		{
			if (!(Expected == Actual))//!(... == ...) rather than (... != ...) to test correct operator
			{
				FailedAssertWithoutMessage<AreEqualDetails<Type>> result(Expected, Actual);
				FailAssert(result);
			}
		}

		template <typename Type>
		void AreEqual(const Type& Expected, const Type& Actual, std::string Message)
		{
			if (!(Expected == Actual))
			{
				FailedAssertWithMessage<AreEqualDetails<Type>> result(std::move(Message), Expected, Actual);
				FailAssert(result);
			}
		}
	};
}