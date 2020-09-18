#include "Engine\Engine.h"
#include "TypeNames\TypeName.h"
#include "LogObject\LogObjectFactory.h"
#include "Test\Test.h"

struct TwoInts
{
	int a;
	int b;
};

template<typename A, typename B>
struct Pair
{
	A a;
	B b;

	constexpr Pair(A a_, B b_) : a(a_), b(b_) {}

	friend bool operator == (const Pair<A, B>& p1, const Pair<A, B>& p2)
	{
		return p1.a == p2.a && p1.b == p2.b;
	}
};

bool operator ==(const TwoInts& t1, const TwoInts& t2)
{
	return t1.a == t2.a && t1.b == t2.b;
}

TwoInts TwoIntsFactory(int a)
{
	return TwoInts{ a, a };
}

template<typename A, typename B>
Pair<A, B>  PairFactory(const A& a, const B& b)
{
	return Pair<A, B>{ a, b };
}

namespace TypeNames
{
	TYPENAME(TwoInts);

	TEMPLATE_TYPENAME(Pair);
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

	template <typename A, typename B>
	class LogObjectFactory<Pair<A, B>>
	{
	public:
		constexpr static decltype(auto) Build(const Pair<A, B>& p)
		{
			return LogObjectFactoryBackend<Pair<A, B>>::Build(p.a, p.b);
		}
	};
}

auto TestFunction()
{

}

auto TestFunction2()
{
	TwoInts a{1, 1};
	TwoInts b = TwoIntsFactory(1);

	auto Test1 = Testing::Assert::AreEqual(a, b);
	return Testing::TestResult(Test1);
}

TESTS_START

TEST_START("FirstTest")
{
	Pair<int, int> a{ 1, 1 };
	Pair<int, int> b = PairFactory(1, 1);

	auto Test1 = Testing::Assert::AreEqual(a, b);
	return Testing::TestResult(Test1);
}
TEST_END

TEST_START("SecondTest")
{
	Pair<int, int> a{ 1, 1 };
	Pair<int, int> b = PairFactory(1, 1);

	auto Test1 = Testing::Assert::AreEqual(a, b);
	return Testing::TestResult(Test1);
}
TEST_END

TESTS_END
