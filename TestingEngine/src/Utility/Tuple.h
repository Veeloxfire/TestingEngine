#pragma once
#include "Traits.h"
namespace Testing
{
	namespace Testing
	{
		template<typename ... Objs>
		class Tuple;

		template<typename First, typename ... Rest>
		class Tuple<First, Rest...> : public Tuple<Rest...>
		{
			First first;

		public:
			constexpr Tuple(First&& f, Rest&&... r)
				: first(std::forward<First>(f)), Tuple<Rest...>(std::forward<Rest>(r)...)
			{}

			constexpr const First& GetFirst() const { return first; }
		};

		template<typename First>
		class Tuple<First>
		{
			First first;

		public:
			constexpr Tuple(First&& f)
				: first(std::forward<First>(f))
			{}

			constexpr const First& GetFirst() const { return first; }
		};

		template<typename ... Objs>
		Tuple(Objs&& ... ts)->Tuple<Objs...>;
	}
}