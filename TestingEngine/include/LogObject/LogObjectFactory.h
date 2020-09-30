#pragma once
#include "LogObject.h"

#include "Utility/BooleanConstructs.h"

#include <string>
#include <sstream>

namespace Testing
{
	template<typename Input>
	class LogObjectFactoryBackend
	{
		template <typename Input>
		friend class LogObjectFactory;
	
	public:
		template <typename ... Types>
		constexpr static LogObject<Input, Types...> Build(Types... t)
		{
			return LogObject<Input, Types...>(std::move(t)...);
		}
	};

	template <typename Input>
	class LogObjectFactory
	{
		static_assert(AlwaysFalse<Input>,
			"User must specify a specialisation of LogObjectFactory - Comment inside MakeLogObject to explain");

		/*
		Use the static function Build in the class LogObjectFactoryBackend to make the LogObject

		You can only use LogObjectFactoryBackend with an object if you have declared "MakeTypeName(...);" somewhere.
		This will allow the LogObject to have the name of a type.

		You only need to do this for the base type e.g. MyObject
		Calling "TYPENAME(MyObject);" will allow you to use LogObjects with MyObject*, const MyObject etc

		If you wish to specify the name as something different, or dont know the exact type then use TYPENAME_SPECIFIEDNAME
		e.g. TYPENAME_SPECIFIEDNAME(decltype(...), "Type")

		If you were to do this normally then the type would be displayed as "decltype(...)" with a pointer of type
		"decltype(...)*". Which, while not incorrect, may be slightly unreadable


		IMPORTANT - Call "TYPENAME(...);" in the "TypeNames" namespace for the types INSIDE return type
					(it does not strictly NEED to be called on the template type)

		NOT COMPATIBLE WITH TEMPLATES YET - duh it uses macros

		FULL EXAMPLE IN GLOBAL NAMESPACE:
			struct TwoInts
			{
				int a;
				int b;
			};

			namespace TypeNames
			{
				TYPENAME(TwoInts);
			}
			
			namespace Testing
			{
				template <>
				class LogObjectFactory<TwoInts>
				{
				public:
					constexpr static decltype(auto) Build(const TwoInts& i)
					{
						return LogObjectFactoryBackend<Input>::Build(i.a, i.b);
					}
				};
			}
		*/

		//This exists so that code doesnt fail immediately
	public:
		constexpr static decltype(auto) Build(const Input& i)
		{
			return LogObjectFactoryBackend::Build(i);
		}
	};
}