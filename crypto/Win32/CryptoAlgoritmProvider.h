#pragma once
#include "../../CryptoData.h"

namespace CommonLib
{
	namespace crypto
	{
		namespace win
		{
			typedef std::shared_ptr<class CBcryptAlgProvider> CBcryptAlgProviderPtr;

			class CBcryptAlgProvider
			{
			public:
				CBcryptAlgProviderPtr Create(LPCWSTR pszAlgId, ULONG dwFlags);
				~CBcryptAlgProvider();

				void BCryptDeriveKeyPBKDF2(const crypto_astr& password, const crypto_vector& salt, uint64_t interations, uint32_t keySize, crypto_vector& derivedKey);
				void BCryptGenRandom(crypto_vector& random, uint32_t size, ULONG dwFlags);

			private:
				CBcryptAlgProvider(BCRYPT_ALG_HANDLE phAlgorithm);
			private:
				BCRYPT_ALG_HANDLE m_hAlgorithm{ 0 };
			};
		}
	}
}