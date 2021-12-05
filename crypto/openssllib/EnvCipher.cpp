#include "stdafx.h"
#include "EnvCipher.h"
#include "OpensslExc.h"

namespace CommonLib
{
	namespace crypto
	{
		namespace openssllib
		{

			CEvpCipher::CEvpCipher(OpenSSLCipherType type)
			{
				switch (type)
				{
				case CommonLib::crypto::openssllib::OpenSSLCipherType::AES_256_ECB:
					m_pCipher = EVP_aes_256_ecb();
					break;
				case CommonLib::crypto::openssllib::OpenSSLCipherType::AES_256_CBC:
					m_pCipher = EVP_aes_256_cbc();
					break;
				case CommonLib::crypto::openssllib::OpenSSLCipherType::AES_256_CCM:
					m_pCipher = EVP_aes_256_ccm();
					break;
				case CommonLib::crypto::openssllib::OpenSSLCipherType::AES_256_GCM:
					m_pCipher = EVP_aes_256_gcm();
					break;
				default:
					throw CExcBase("EvpCipher unknown cipher type: %1", (int)type);

				}

				if (m_pCipher == nullptr)
					throw COpenSSLExc("EvpCipher: Failed to create");

			}

			CEvpCipher::~CEvpCipher()
			{

			}

 
			const EVP_CIPHER* CEvpCipher::GetCipher() const
			{
				return m_pCipher;
			}
		}
	}
}