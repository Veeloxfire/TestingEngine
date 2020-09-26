#pragma once
#include "Test.h"
namespace Testing
{
	template<IsTest ... TestObjs>
	class Tests;

	template<IsTest First, IsTest ... Rest>
	class Tests<First, Rest...> : public Tests<Rest...>
	{
		First first;
		
	public:
		constexpr Tests(First&& f, Rest&&... r)
			: first(std::forward<First>(f)), Tests<Rest...>(std::forward<Rest>(r)...)
		{}

		const First& GetFirst() const { return first; }
	};

	template<IsTest First>
	class Tests<First>
	{
		First first;

	public:
		constexpr Tests(First&& f)
			: first(std::forward<First>(f))
		{}

		const First& GetFirst() const { return first; }
	};

	template<IsTest ... TestObjs>
	Tests(TestObjs&& ... ts)->Tests<RemoveReference<TestObjs>...>;
}