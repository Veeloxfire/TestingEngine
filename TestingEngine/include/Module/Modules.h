#pragma once
#include "Module.h"
namespace Testing
{
	template<IsModule ... ModuleObjs>
	class Modules;

	template<IsModule First, IsModule ... Rest>
	class Modules<First, Rest...> : public Modules<Rest...>
	{
		First first;

	public:
		constexpr Modules(First&& f, Rest&&... r)
			: first(std::forward<First>(f)), Modules<Rest...>(std::forward<Rest>(r)...)
		{}

		const First& GetFirst() const { return first; }
	};

	template<IsModule First>
	class Modules<First>
	{
		First first;

	public:
		constexpr Modules(First&& f)
			: first(std::forward<First>(f))
		{}

		const First& GetFirst() const { return first; }
	};

	template<IsModule ... ModuleObjs>
	Modules(ModuleObjs&& ... ts)->Modules<RemoveReference<ModuleObjs>...>;
}