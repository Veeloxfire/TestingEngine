#pragma once

namespace Testing
{
	template <typename ... T>
	constexpr static bool AlwaysFalse = false;

	template <typename ... T>
	constexpr static bool AlwaysTrue  = true;

	template <bool b>
	struct BoolStruct
	{
		constexpr static bool value = b;
	};

	using False = BoolStruct<false>;
	using True  = BoolStruct<true>;

}