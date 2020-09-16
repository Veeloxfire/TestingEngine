#pragma once
namespace TypeNames
{
	template<typename T, unsigned int Size>
	struct Array
	{
		friend class ArrayFactory;

		T Arr[Size] = {};
		static constexpr unsigned int GetSize() { return Size; }

		constexpr Array() {}
	};
	
	class ArrayFactory {
	public:
		template<typename T, unsigned int Size>
		constexpr static Array<T, Size> Make(const T(&in_arr)[Size])
		{
			Array<T, Size> Arr;
			for (unsigned int i = 0; i < Size; i++)
				Arr.Arr[i] = in_arr[i];
			return Arr;
		}

		template <typename T, unsigned int A, unsigned int B>
		constexpr static Array<T, A + B> Make(const T(&in_arr1)[A], const T(&in_arr2)[B])
		{
			Array<T, A + B> Arr;

			for (unsigned int i = 0; i < A; i++)
				Arr.Arr[i] = in_arr1[i];

			for (unsigned int i = 0; i < B; i++)
				Arr.Arr[i + A] = in_arr2[i];

			return Arr;
		}

		template <unsigned int Overlap, typename T, unsigned int A, unsigned int B>
		constexpr static Array<T, A + B - Overlap> MakeOverlap(const T(&in_arr1)[A], const T(&in_arr2)[B])
		{
			static_assert(A >= Overlap, "");
			Array<T, A + B - Overlap> Arr;

			for (unsigned int i = 0; i < A - Overlap; i++)
				Arr.Arr[i] = in_arr1[i];

			for (unsigned int i = 0; i < B; i++)
				Arr.Arr[i + A - Overlap] = in_arr2[i];

			return Arr;
		}

		template<typename T, unsigned int Size>
		constexpr static Array<T, Size> Make(const Array<T, Size>& arr)
		{
			return Make(arr.Arr);
		}

		template <typename T, unsigned int A, unsigned int B>
		constexpr static Array<T, A + B> Make(const Array<T, A>& arr1, const Array<T, B>& arr2)
		{
			return Make(arr1.Arr, arr2.Arr);
		}

		template <typename T, unsigned int A, unsigned int B>
		constexpr static Array<T, A + B> Make(const T(&in_arr1)[A], const Array<T, B>& arr2)
		{
			return Make(in_arr1, arr2.Arr);
		}

		template <typename T, unsigned int A, unsigned int B>
		constexpr static Array<T, A + B> Make(const Array<T, A>& arr1, const T(&in_arr2)[B])
		{
			return Make(arr1.Arr, in_arr2);
		}

		template <typename T, unsigned int A, unsigned int B>
		constexpr static Array<T, A + B - 1> ConcatStrings(const Array<T, A>& arr1, const Array<T, B>& arr2)
		{
			return MakeOverlap<1>(arr1.Arr, arr2.Arr);
		}

		template <typename T, unsigned int A, unsigned int B>
		constexpr static Array<T, A + B - 1> ConcatStrings(const T(&in_arr1)[A], const Array<T, B>& arr2)
		{
			return MakeOverlap<1>(in_arr1, arr2.Arr);
		}

		template <typename T, unsigned int A, unsigned int B>
		constexpr static Array<T, A + B - 1> ConcatStrings(const Array<T, A>& arr1, const T(&in_arr2)[B])
		{
			return MakeOverlap<1>(arr1.Arr, in_arr2);
		}
	};

	class ArrayHelper
	{
	public:
		template<typename T, unsigned int Size>
		static constexpr unsigned int Size(const T(&in_arr)[Size])
		{
			return Size;
		}
	};
}