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

class TwoIntsTest : public Testing::Test
{
public:
	TwoIntsTest(Testing::EngineAPI& api) : Testing::Test(api)
	{}


	const char* GetName() const override { constexpr static const char* Name = "TwoIntsTest"; return Name; }

	void TestFunction() override
	{
		TwoInts a{ 1, 2 };
		TwoInts b = TwoIntsFactory(1);
		Assert.AreEqual(a, b);
	}
};


int main()
{
	Testing::Engine engine;
	TwoIntsTest test(engine);

	engine.SetTests(&test, 1);
	engine.RunAllTests();
	return 0;
}