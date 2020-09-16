#pragma once
#include "Traits.h"
#include "Allocator.h"

namespace Testing
{
	class Empty {
	public:
		constexpr Empty() = default;
		constexpr Empty(const Empty& E) = default;
		constexpr Empty(Empty&& E) = default;
	};

	constexpr static Empty EmptyVal = {};

	template <typename T>
	class OptionalTrivialHolder
	{
	protected:
		union
		{
			Empty empty;
			T notEmpty;
		};

		bool m_HasValue;

	public:
		constexpr OptionalTrivialHolder() : empty(), m_HasValue(false) {}
		constexpr OptionalTrivialHolder(const Empty& E) : empty(), m_HasValue(false) {}
		constexpr OptionalTrivialHolder(const T& t) : notEmpty(t), m_HasValue(false) {}

		constexpr OptionalTrivialHolder(const OptionalTrivialHolder<T>& o) = default;
		constexpr OptionalTrivialHolder(OptionalTrivialHolder<T>&& o) = default;

		template<typename ... Ts>
		constexpr OptionalTrivialHolder(Ts&& ... ts) : notEmpty(std::forward<Ts>(ts)...), m_HasValue(true) {}
	};

	template <typename T>
	class OptionalNonTrivialHolder
	{
	protected:
		union
		{
			Empty empty;
			T notEmpty;
		};

		bool m_HasValue;
	public:
		constexpr OptionalNonTrivialHolder() : empty(), m_HasValue(false) {}
		constexpr OptionalNonTrivialHolder(const Empty& E) : empty(), m_HasValue(false) {}
		constexpr OptionalNonTrivialHolder(const T& t) : notEmpty(t), m_HasValue(true) {}

		constexpr OptionalNonTrivialHolder(const OptionalNonTrivialHolder<T>& o) = default;
		constexpr OptionalNonTrivialHolder(OptionalNonTrivialHolder<T>&& o) = default;

		template<typename ... Ts>
		constexpr OptionalNonTrivialHolder(Ts&& ... ts) : notEmpty(std::forward<Ts>(ts)...), m_HasValue(true) {}

		~OptionalNonTrivialHolder()
		{
			if (m_HasValue)
			{
				notEmpty.~T();
			}
		}
	};

	template<typename T>
	class Optional : Conditional<IsTriviallyDestructable<T>, OptionalTrivialHolder<T>, OptionalNonTrivialHolder<T>>
	{
		using Backend = Conditional<
			IsTriviallyDestructable<T>,
			OptionalTrivialHolder<T>,
			OptionalNonTrivialHolder<T>
		>;

	public:
		constexpr Optional() : Backend() {}
		constexpr Optional(const Empty& e) : Backend(e) {}
		constexpr Optional(const T& t) : Backend(t) {}
		
		constexpr Optional(const Optional<T>& o) = default;
		constexpr Optional(Optional<T>&& o) = default;

		template<typename ... Ts>
		constexpr Optional(Ts&& ... ts) : Backend(std::forward<Ts>(ts)...) {}

		bool HasValue() const
		{
			return m_HasValue;
		}

		constexpr void Empty()
		{
			if (m_HasValue) Allocator::Destruct(notEmpty);
			m_HasValue = false;
		}

		template<typename ... Ts>
		constexpr void Emplace(Ts&& ... ts)
		{
			Empty();

			Allocator::Construct::InPlace(notEmpty, std::foward<Ts>(ts)...);
			m_HasValue = true;
		}

		const T& operator->() const
		{
			return notEmpty;
		}

		T& operator->()
		{
			return notEmpty;
		}
	};
}