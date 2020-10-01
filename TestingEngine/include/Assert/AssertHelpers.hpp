#pragma once
#include "../TypeNames/TypeName.h"
#include "../LogObject/LogObjectFactory.h"
namespace Testing
{
	namespace AssertHelpers
	{
		class Empty {};
		
		[[nodiscard]] constexpr Empty&& GetEmptyRValRef() { return Empty(); }

		[[nodiscard]] constexpr Empty& GetEmptyNonConstRef()
		{ 
			Empty e;
			return e;
		}

		[[nodiscard]] constexpr const Empty& GetEmptyConstRef()
		{ 
			Empty e;
			return Empty();
		}

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