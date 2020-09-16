#pragma once
#include "Assert\AssertLambda.h"
#include "Utility\Traits.h"
namespace Testing
{
	template<typename ... Lambdas>
	class TestResult;

	template<typename Last>
	class TestResult<Last>
	{
		static_assert(IsBaseOf<AssertLambdaBase, Last>::value, "TestResult template argument must be AssertLambda");
		using Result = typename Last::ReturnType;

		const Result first;

	public:
		constexpr TestResult(const Last& F) : first(F())
		{}
	};

	template<typename First, typename ... Rest>
	class TestResult<First, Rest...> : public TestResult<Rest...>
	{
		static_assert(IsBaseOf<AssertLambdaBase, First>::value, "TestResult template argument must be AssertLambda");
		using Result = typename First::ReturnType;

		const Result first;
	public:
		constexpr TestResult(const First& F, const Rest& ... R) : first(F()), TestResult<Rest...>(R)
		{}
	};

	template<typename ... Lambdas>
	TestResult(const Lambdas& ... L)->TestResult<Lambdas...>;
}