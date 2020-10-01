#pragma once
#include "../TypeNames/TypeName.h"
#include "../LogObject/LogObjectFactory.h"
namespace Testing
{
	namespace AssertHelpers
	{
		class Empty {};
		
		[[nodiscard]] constexpr Empty&& GetEmptyRValRef() noexcept { return Empty(); }

		[[nodiscard]] constexpr Empty& GetEmptyNonConstRef() noexcept
		{ 
			Empty e{};
			return e;
		}

		[[nodiscard]] constexpr const Empty& GetEmptyConstRef()	noexcept { return Empty(); }

		enum class ConstructorType
		{
			RValRef, ConstRef, NonConstRef
		};

		class ConstructorChecker
		{
			const ConstructorType type;

		public:
			constexpr ConstructorChecker([[maybe_unused]] Empty& e) : type(ConstructorType::NonConstRef)
			{}
			constexpr ConstructorChecker([[maybe_unused]] const Empty& e) : type(ConstructorType::ConstRef)
			{}
			constexpr ConstructorChecker([[maybe_unused]] Empty&& e) : type(ConstructorType::RValRef)
			{}

			[[nodiscard]] constexpr ConstructorType GetType() const noexcept
			{
				return type;
			}
		};
	}
}

namespace TypeNames
{
	TYPENAME(Testing::AssertHelpers::ConstructorType);
}

namespace Testing
{
	LogObjectFactoryForWholeType(AssertHelpers::ConstructorType);
}