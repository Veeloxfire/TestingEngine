#pragma once
#include "../TypeNames/TypeName.h"
#include "../LogObject/LogObjectFactory.h"
namespace Testing
{
	namespace AssertHelpers
	{
		class ToyClass {};

		enum class ConstructorType
		{
			RValRef, ConstRef, NonConstRef
		};

		template<typename T>
		class ConstructorChecker
		{
			const ConstructorType type;

		public:
			constexpr ConstructorChecker([[maybe_unused]] T& e) : type(ConstructorType::NonConstRef)
			{}
			constexpr ConstructorChecker([[maybe_unused]] const T& e) : type(ConstructorType::ConstRef)
			{}
			constexpr ConstructorChecker([[maybe_unused]] T&& e) : type(ConstructorType::RValRef)
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

	LogObjectFactoryForStreamableType(AssertHelpers::ConstructorType);

	std::ostream& operator<<(std::ostream& stream, const AssertHelpers::ConstructorType i)
	{
		switch (i)
		{
		case AssertHelpers::ConstructorType::RValRef: return stream << "RValRef";
		case AssertHelpers::ConstructorType::ConstRef: return stream << "ConstRef";
		case AssertHelpers::ConstructorType::NonConstRef: return stream << "NonConstRef";
		}

		return stream << "Unknown ConstructorType";
	}
}