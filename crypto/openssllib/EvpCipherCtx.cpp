#include "stdafx.h"
#include "EvpCipherCtx.h"
#include "OpensslExc.h"

namespace CommonLib
{
	namespace crypto
	{
		namespace openssllib
		{
			CEvpCipherCtx::CEvpCipherCtx()
			{
				m_pCipherCtx = EVP_CIPHER_CTX_new();
				if (m_pCipherCtx == nullptr)
					throw COpenSSLExc("EvpCipherCtx: Failed to create");
			}

			CEvpCipherCtx::~CEvpCipherCtx()
			{

			}
		}
	}
}