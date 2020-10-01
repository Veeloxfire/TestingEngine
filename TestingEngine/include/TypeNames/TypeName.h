#pragma once
#include "../Utility/BooleanConstructs.h"
#include "../Utility/Traits.h"
#include "Array.h"

namespace TypeNames
{
	template <typename T>
	struct TypeName : public Testing::False
	{
		constexpr static Array Arr = ArrayFactory::Make("");
		constexpr static const char* name = Arr.Arr;
	};

#ifdef POST_CONST
	template <typename T>
	struct TypeName<T const> : public Testing::IsBaseOf<Testing::True, TypeName<T>>
	{
		constexpr static Array Arr = ArrayFactory::ConcatStrings(TypeName<T>::Arr, " const");
		constexpr static const char* name = Arr.Arr;
	};
#else
	template <typename T>
	struct TypeName<const T> : public Testing::IsBaseOf<Testing::True, TypeName<T>>
	{
		constexpr static Array Arr = ArrayFactory::ConcatStrings("const ", TypeName<T>::Arr);
		constexpr static const char* name = Arr.Arr;
	};

	template <typename T>
	struct TypeName<T* const> : public Testing::IsBaseOf<Testing::True, TypeName<T>>
	{
		constexpr static Array Arr = ArrayFactory::ConcatStrings(TypeName<T>::Arr, "* const");
		constexpr static const char* name = Arr.Arr;
	};
#endif

	template <typename T>
	struct TypeName<T*> : public Testing::IsBaseOf<Testing::True, TypeName<T>>
	{
		constexpr static Array Arr = ArrayFactory::ConcatStrings(TypeName<T>::Arr, "*");
		constexpr static const char* name = Arr.Arr;
	};

	template <typename T>
	struct TypeName<T&> : public Testing::IsBaseOf<Testing::True, TypeName<T>>
	{
		constexpr static Array Arr = ArrayFactory::ConcatStrings(TypeName<T>::Arr, "&");
		constexpr static const char* name = Arr.Arr;
	};

	template <typename T>
	struct TypeName<T&&> : public Testing::IsBaseOf<Testing::True, TypeName<T>>
	{
		constexpr static Array Arr = ArrayFactory::ConcatStrings(TypeName<T>::Arr, "&&");
		constexpr static const char* name = Arr.Arr;
	};

#define TEMPLATE_TYPENAME_SPECIFIEDNAME(type, string)                                        \
	template <typename ... T>                                                                \
	struct TypeName<type<T...>> : public Testing::IsAllBaseOf<Testing::True, TypeName<T>...> \
	{                                                                                        \
		constexpr static Array AllTypes = ArrayFactory::ConcatTypeNames(TypeName<T>::Arr...);\
		constexpr static Array Arr = ArrayFactory::ConcatStrings(ArrayFactory::Make(string), \
																  "<",                       \
																  AllTypes,                  \
																  ">");                      \
		constexpr static const char* name = Arr.Arr;                                         \
	}

#define TYPENAME_SPECIFIEDNAME(type, string)                    \
	template <>                                                 \
	struct TypeName<type> : public Testing::True                \
	{                                                           \
		constexpr static Array Arr = ArrayFactory::Make(string);\
		constexpr static const char* name = Arr.Arr;            \
	}

#define TYPENAME(type) TYPENAME_SPECIFIEDNAME(type, #type)
#define TEMPLATE_TYPENAME(type) TEMPLATE_TYPENAME_SPECIFIEDNAME(type, #type)

	//Fundamental Types
	TYPENAME(void);
	TYPENAME(bool);

	TYPENAME(short);
	TYPENAME(unsigned short);
	TYPENAME(int);
	TYPENAME(unsigned int);
	TYPENAME(long);
	TYPENAME(unsigned long);
	TYPENAME(long long);
	TYPENAME(unsigned long long);

	TYPENAME(char);
	TYPENAME(unsigned char);
	TYPENAME(signed char);
	TYPENAME(wchar_t);
	TYPENAME(char16_t);
	TYPENAME(char32_t);

	TYPENAME(float);
	TYPENAME(double);
	TYPENAME(long double);

}


