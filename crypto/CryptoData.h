#pragma once
#include <vector>

namespace CommonLib
{
	namespace crypto
	{

		template <typename T>
		class crypto_alloc : public std::allocator<T>
		{
		public:
			void deallocate(T * const _Ptr, const size_t _Count)
			{
				memset(_Ptr, 0, _Count);
				std::allocator<T>::deallocate(_Ptr, _Count);
			}
		};

		typedef  std::vector<byte_t, crypto_alloc<byte_t> > crypto_vector;
		typedef std::basic_string<char, std::char_traits<char>, crypto_alloc<char> > crypto_astr;

	}
}