#include "Engine\Engine.h"
#include "Utility\TypeName.h"
#include "LogObject\LogObjectFactory.h"
#include "Test\Test.h"

struct TwoInts
{
	int a;
	int b;
};

bool operator ==(const TwoInts& t1, const TwoInts& t2)
{
	return t1.a == t2.a && t1.b == t2.b;
}

TwoInts TwoIntsFactory(int a)
{
	return TwoInts{ a, a };
}

namespace TypeNames
{
	TYPENAME(TwoInts);
}

namespace Testing
{
	template <>
	class LogObjectFactory<TwoInts>
	{
	public:
		constexpr static decltype(auto) Build(const TwoInts& i)
		{
			return LogObjectFactoryBackend<TwoInts>::Build(i.a, i.b);
		}
	};
}

auto TestFunction()
{
	TwoInts a{ 1, 2 };
	TwoInts b = TwoIntsFactory(1);
	auto Test1 = Testing::Assert::AreEqual(a, b);
	return Testing::TestResult(Test1);
}

int main()
{
	Testing::Test t("FirstTest", &TestFunction);

	Testing::Engine engine(t);

	engine.RunAllTests();
	return 0;
}