#pragma once
#include <utility>

namespace Testing
{
	namespace Allocator
	{
		namespace Construct
		{
			template<typename Type, typename ... Args>
			constexpr static void InPlace(Type& Obj, Args&& ... args) {
				new(&Obj) Type{ std::forward<Args>(args)... };
			}
		}

		template<typename Type>
		constexpr static void Destruct(Type& Place) {
			Place.~Type();
		}
	}
}