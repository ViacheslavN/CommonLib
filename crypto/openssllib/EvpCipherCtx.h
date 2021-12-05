#pragma once
 
#include <openssl/evp.h>

#include "../crypto.h"

namespace CommonLib
{
	namespace crypto
	{
		namespace openssllib
		{
			class CEvpCipherCtx
			{
			public:
				CEvpCipherCtx();
				~CEvpCipherCtx();

				int EVP_EncryptInit_ex(EVP_CIPHER_CTX *ctx, const EVP_CIPHER *type,
					ENGINE *impl, const unsigned char *key, const unsigned char *iv);

			private:
				EVP_CIPHER_CTX* m_pCipherCtx;
			};
		}
	}
}