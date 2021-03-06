#pragma once
#include <string>
#include "..\IO\IO.h"

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
		constexpr static const char Name[] = "AreEqual";

		constexpr AreEqualDetails(Type&& e, Type&& a)
			: ComparisonDetails<Type>(std::forward<Type>(e), std::forward<Type>(a))
		{}

		[[nodiscard]] static constexpr bool AssertBool(const Type& e, const Type& a)
		{
			return e == a;
		}
	};

	template <typename Type>
	class AreNotEqualDetails : public ComparisonDetails<Type>
	{
	public:
		constexpr static const char Name[] = "AreNotEqual";

		constexpr AreNotEqualDetails(Type&& e, Type&& a)
			: ComparisonDetails<Type>(std::forward<Type>(e), std::forward<Type>(a))
		{}

		[[nodiscard]] static constexpr bool AssertBool(const Type& e, const Type& a)
		{
			return e != a;
		}
	};

	template <typename Expected, typename Actual>
	class TypeComparisonDetails
	{
	public:
		static_assert(TypeNames::TypeName<Expected>::value, "TypeName for expected class has not been declared");
		static_assert(TypeNames::TypeName<Actual>::value, "TypeName for actual class has not been declared");

		constexpr TypeComparisonDetails() = default;

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
			IO::LogString(TypeNames::TypeName<Expected>::name);
			IO::IndentIn();
		}

		void LogActual() const
		{
			IO::LogString("Actual:");

			IO::IndentOut();
			IO::LogString(TypeNames::TypeName<Actual>::name);
			IO::IndentIn();
		}
	};

	template <typename Expected, typename Actual>
	class AreSameTypeDetails : public TypeComparisonDetails<Expected, Actual>
	{
	public:
		constexpr static const char Name[] = "AreSameType";

		constexpr AreSameTypeDetails() = default;

		[[nodiscard]] static constexpr bool AssertBool() noexcept
		{
			return IsSame<Expected, Actual>::value;
		}
	};

	template<typename L>
	class LambdaDetails
	{
		L lambda;
	public:
		constexpr LambdaDetails(L&& l) : lambda(l) {}

		void LogDetails() const
		{
			IO::LogString("Executable-Object");
		}
	};

	template<typename L>
	class ShouldThrowDetails : public LambdaDetails<L>
	{
	public:
		constexpr ShouldThrowDetails(L&& l) : LambdaDetails<L>(std::forward<L>(l))
		{}

		constexpr static const char Name[] = "ShouldThrow";

		[[nodiscard]] static constexpr bool AssertBool(const L& l)
		{
			try
			{
				l();
				return false;
			}
			catch (...)
			{
				return true;
			}
		}
	};
}