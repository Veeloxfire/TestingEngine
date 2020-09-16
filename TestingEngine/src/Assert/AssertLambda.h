#pragma once


namespace Testing
{
	class AssertLambdaBase {};

	template<typename T>
	class AssertLambda : public AssertLambdaBase
	{
		const T lambda;
	public:
		using ReturnType = decltype(lambda());

		constexpr AssertLambda(T&& l) : lambda(std::forward<T>(l)) {}

		constexpr auto operator()() const
		{
			return lambda();
		}
	};

	template<typename T>
	AssertLambda(T&& l)->AssertLambda<T>;
}