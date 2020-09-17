#pragma once
#include "Assert\AssertResultAPI.h"
#include "Utility\Traits.h"
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
		constexpr TestResult(Last& F) : first(std::move(F))
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
		constexpr TestResult(First& F, Rest& ... R) : first(std::move(F)), TestResult<Rest...>(R...)
		{}
		constexpr TestResult(const First& F, Rest& ... R) : first(F), TestResult<Rest...>(R...)
		{}

		constexpr const First& GetFirst() const { return first; }
	};

	template<typename ... Results>
	TestResult(Results& ... L)->TestResult<Results...>;
}