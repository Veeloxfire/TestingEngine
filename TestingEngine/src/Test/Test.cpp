#include "Test.h"

namespace Testing
{
	bool Test::RunCode()
	{
		TestFunction();
		return Assert.HasFailed();
	}
}