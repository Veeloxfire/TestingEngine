#pragma once
#include "Test.h"
namespace Testing
{
	template<typename ... TestObjs>
	class Tests;

	template<typename First, typename ... Rest>
	class Tests<First, Rest...> : public Tests<Rest...>
	{
		static_assert(IsBaseOf<TestBase, First>::value, "Must be a test type");
		First first;
		
	public:
		constexpr Tests(First&& f, Rest&&... r)
			: first(std::forward<First>(f)), Tests<Rest...>(std::forward<Rest>(r)...)
		{}

		const First& GetFirst() const { return first; }
	};

	template<typename First>
	class Tests<First>
	{
		static_assert(IsBaseOf<TestBase, First>::value, "Must be a test type");
		First first;

	public:
		constexpr Tests(First&& f)
			: first(std::forward<First>(f))
		{}

		const First& GetFirst() const { return first; }
	};

	template<typename ... TestObjs>
	Tests(TestObjs&& ... ts)->Tests<TestObjs...>;
}