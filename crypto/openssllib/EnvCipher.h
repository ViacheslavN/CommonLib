#pragma once

#include <openssl/evp.h>

#include "../crypto.h"

namespace CommonLib
{
	namespace crypto
	{
		namespace openssllib
		{
			typedef std::shared_ptr<class CEvpCipher> CEvpCipherPtr;

			enum class OpenSSLCipherType
			{
				AES_256_ECB,
				AES_256_CBC,
				AES_256_CCM,
				AES_256_GCM
			};

			class CEvpCipher
			{
			public:
				CEvpCipher(OpenSSLCipherType type);
				~CEvpCipher();

				 const EVP_CIPHER* GetCipher() const;
			private:
				const  EVP_CIPHER* m_pCipher;
			};
		}
	}
}