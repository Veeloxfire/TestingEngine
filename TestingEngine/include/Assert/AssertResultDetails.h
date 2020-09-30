#pragma once
#include <string>
#include "IO\IO.h"

namespace Testing
{
	template <typename Type>
	class ComparisonDetails
	{
	public:
		Type Expected;
		Type Actual;
	public:
		constexpr ComparisonDetails(Type&& e, Type&& a)
			:Expected(std::forward<Type>(e)), Actual(std::forward<Type>(a))
		{}

		void LogDetails() const
		{
			LogExpected();
			LogActual();
		}

	private:
		void LogExpected() const
		{
			IO::LogString("Expected:");

			IO::IndentOut();
			IO::LogObject(Expected);
			IO::IndentIn();
		}

		void LogActual() const
		{
			IO::LogString("Actual:");

			IO::IndentOut();
			IO::LogObject(Actual);
			IO::IndentIn();
		}
	};

	template <typename Type>
	class AreEqualDetails : public ComparisonDetails<Type>
	{
	public:
		constexpr static const char* Name = "AreEqual";

		constexpr AreEqualDetails(Type&& e, Type&& a)
			: ComparisonDetails<Type>(std::forward<Type>(e), std::forward<Type>(a))
		{}

		inline static constexpr bool AssertBool(const Type& e, const Type& a)
		{
			return e == a;
		}
	};

	template <typename Type>
	class AreNotEqualDetails : public ComparisonDetails<Type>
	{
	public:
		constexpr static const char* Name = "AreNotEqual";

		constexpr AreNotEqualDetails(Type&& e, Type&& a)
			: ComparisonDetails<Type>(std::forward<Type>(e), std::forward<Type>(a))
		{}

		inline static constexpr bool AssertBool(const Type& e, const Type& a)
		{
			return e != a;
		}
	};
}