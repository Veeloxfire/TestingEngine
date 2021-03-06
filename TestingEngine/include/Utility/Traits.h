#pragma once
#include "BooleanConstructs.h"

namespace Testing
{
	template<typename T>
	struct ConstOfHelper
	{
		using Type = const T;
	};

	template<typename T>
	struct ConstOfHelper<const T>
	{
		using Type = const T;
	};

	template<typename T>
	using ConstOf = typename ConstOfHelper<T>::Type;

	template<typename T>
	auto Unevaluated()->T&&;

	template<typename T>
	using ReturnTypeOf = decltype(Unevaluated<T>()());

	template<typename T, typename ... ArgTypes>
	using ReturnTypeOfArgs = decltype(Unevaluated<T>()(Unevaluated<ArgTypes>()...));

	template<typename T>
	struct RemoveReferenceHelper
	{
		using Type = T;
	};

	template<typename T>
	struct RemoveReferenceHelper<T&>
	{
		using Type = T;
	};

	template<typename T>
	struct RemoveReferenceHelper<T&&>
	{
		using Type = T;
	};

	template<typename T>
	using RemoveReference = typename RemoveReferenceHelper<T>::Type;

	template<typename T>
	struct IsReferenceHelper
	{
		using Type = False;
	};

	template<typename T>
	struct IsReferenceHelper<T&>
	{
		using Type = True;
	};

	template<typename T>
	using IsReferenceType = typename IsReferenceHelper<T>::Type;

	template<typename T, typename U>
	struct IsSame_Helper
	{
		using Type = False;
	};

	template<typename T>
	struct IsSame_Helper<T, T>
	{
		using Type = True;
	};

	template<typename T, typename U>
	using IsSame = typename IsSame_Helper<T, U>::Type;

	template <typename T>
	class IsClass_Helper
	{
		template <typename U>
		static True test(int U::*);
		template <typename U>
		static False test(...);

	public:
		using Type = decltype(test<T>(0));
	};

	template <typename T>
	using IsClass = typename IsClass_Helper<T>::Type;

	template <typename Base, typename Derived>
	class IsBaseOf_Helper {
		static True CastCheck(const volatile Base*);
		static False CastCheck(const volatile void*);

	public:
		using Type = BoolStruct <
			decltype(CastCheck(static_cast<Derived*>(nullptr)))::value &&
			IsClass<Base>::value &&
			IsClass<Derived>::value
		>;
	};

	template <typename Base, typename Derived>
	using IsBaseOf = typename IsBaseOf_Helper<RemoveReference<Base>, RemoveReference<Derived>>::Type;

	template <typename Base, typename ... Derived>
	using IsAllBaseOf = And<IsBaseOf<Base, Derived>...>;

	//Warning - Derived is FIRST argument unlike in IsBaseOf
	template<typename Derived, typename Base>
	concept BaseOf = IsBaseOf<Base, Derived>::value;

	template<bool B, class T, class F> //Dont need this but it makes it neater
	struct ConditionalHelper;

	template<class T, class F>
	struct ConditionalHelper<true, T, F> { using Type = F; };

	template<class T, class F>
	struct ConditionalHelper<false, T, F> { using Type = T; };

	template<bool B, class T, class F>
	using Conditional = typename ConditionalHelper<B, T, F>::Type;

#ifdef _MSC_VER
	template<typename T>
	constexpr bool IsTriviallyDestructable = __is_trivially_destructible(T);
#elif __GNUC__
	template<typename T>
	constexpr bool IsTriviallyDestructable = __has_trivial_destructor(T);
#elif __clang__
	template<typename T>
	constexpr bool IsTriviallyDestructable = __is_trivially_destructible(T);
#else
	static_assert(false, "Compiler Unsupported")
#endif
}