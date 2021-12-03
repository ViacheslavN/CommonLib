#pragma once
//F:\ThirdParty\OpenSSL\openssl - 3.0.0\Lib\x64\Debug\include
//F:\work\MyProject\CommonLib\crypto\openssllib\EvpCipherCtx.h
#include <openssl/evp.h>

#include "../crypto.h"

namespace CommonLib
{
	namespace crypto
	{
		namespace winapi
		{
			class CEvpCipherCtx
			{
			public:
				CEvpCipherCtx();
				~CEvpCipherCtx();
			private:
				EVP_CIPHER_CTX* m_pCipherCtx;
			};
		}
	}
}