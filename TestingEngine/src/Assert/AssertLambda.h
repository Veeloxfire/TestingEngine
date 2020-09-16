#pragma once


namespace Testing
{
	class AssertLambdaBase {};

	template<typename T>
	class AssertLambda : public AssertLambdaBase
	{
		const T lambda;
		using ReturnType = decltype(lambda());
	public:
		constexpr AssertLambda(T&& l) : lambda(std::forward<T>(lambda) {}

		constexpr auto operator()() const
		{
			return lambda();
		}
	};

	template<typename T>
	AssertLambda(T&& l)->AssertLambda<T>;
}