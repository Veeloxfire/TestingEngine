#pragma once
#include "Utility/TypeName.h"
#include <utility>
namespace Testing
{
	class LogObjectBase {}; //For use in IsBaseOf

	template<typename Top, typename ... Types>
	class LogObject;

	template<typename Top, typename First, typename ... Rest>
	class LogObject<Top, First, Rest...> : public LogObject<Top, Rest...>
	{
		static_assert(TypeNames::TypeName<First>::value, "TypeName for this class has not been declared");

		template<typename Input>
		friend class LogObjectFactoryBackend;

		First first;
	
		constexpr LogObject(First&& f, Rest&&... r)
			: first( std::move(f) ), LogObject<Top, Rest...>( std::move(r)... )
		{}

	public:
		const LogObject<Top, Rest...>& NextObj() const
		{
			return	*this;
		}

		const char* const GetFirstName() const { return TypeNames::TypeName<First>::name; }
		const First& GetFirst() const { return first; }
	};

	template<typename Top, typename First>
	class LogObject<Top, First> : public LogObjectBase
	{
		static_assert(TypeNames::TypeName<Top>::value, "TypeName for class in LogObject has not been declared");
		static_assert(TypeNames::TypeName<First>::value, "TypeName for class in LogObject has not been declared");
		
		template<typename Input>
		friend class LogObjectFactoryBackend;

		First first;

	public:
		constexpr LogObject(const First& l)
			:first(std::move(l))
		{}

		const char* const GetFirstName() const { return TypeNames::TypeName<First>::name; }
		const First& GetFirst() const { return first; }
	};
}