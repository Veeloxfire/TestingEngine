#pragma once
#include "..\Assert\AssertResultAPI.h"
#include "..\Utility\Traits.h"
namespace Testing
{
	class TestResultBase {};

	template<typename ... Lambdas>
	class TestResult;

	template<typename Last>
	class TestResult<Last> : public TestResultBase
	{
		static_assert(IsBaseOf<AssertResultAPI, Last>::value, "TestResult template argument must be AssertResultAPI");

		ConstOf<Last> first;

	public:
		bool Failed() const {return first.AssertFailed(); }

		constexpr TestResult(Last&& F) : first(std::forward<Last>(F))
		{}
		constexpr TestResult(const Last& F) : first(F)
		{}

		constexpr const Last& GetFirst() const { return first; }
	};

	template<typename First, typename ... Rest>
	class TestResult<First, Rest...> : public TestResult<Rest...>
	{
		static_assert(IsBaseOf<AssertResultAPI, First>::value, "TestResult template argument must be AssertResultAPI");

		ConstOf<First> first;
	public:
		bool Failed() const { return first.AssertFailed() || TestResult<Rest...>::Failed(); }

		constexpr TestResult(First&& F, Rest&& ... R)
			: first(std::forward<First>(F)), TestResult<Rest>(std::forward<Rest>(R)...)
		{}
		constexpr TestResult(const First& F, Rest& ... R) : first(F), TestResult<Rest...>(R...)
		{}

		constexpr const First& GetFirst() const { return first; }
	};

	template<typename ... Results>
	TestResult(Results& ... L)->TestResult<Results...>;
}