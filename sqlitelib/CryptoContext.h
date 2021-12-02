#pragma once
#include "Database.h"
#include "../crypto/XTSBlockChiper.h"
namespace CommonLib
{
	namespace sqlite
	{
		class CCryptoContext : public ICryptoContext
		{
		public:

			CCryptoContext(const crypto::crypto_astr& password, EKeyCryptoType cryptoType);
			CCryptoContext(const crypto::crypto_astr& password);
			virtual ~CCryptoContext();

			virtual crypto::IXTSDataCipherPtr GetXTSDataCipher();
			virtual size_t GetInitBlockSize() const;
			virtual void CreateInitBlock(byte_t *pBuf, size_t size);
			virtual bool ValidateInitBlock(byte_t *pBuf, size_t size);
		private:
			void FillPageWithRandomData(CommonLib::crypto::IRandomGeneratorPtr ptrRandomGenerator, CommonLib::crypto::IKeyGeneratorPtr ptrKeyGenerator, byte_t *pBuf, size_t size);
		private:
			static const uint32_t INIT_BLOCK_SIZE = 8192;
			static const uint32_t CRYPTO_BLOCK_SZIE = 4096;
			static const uint32_t SALT_SZIE = 32;
			static const uint32_t PWD_KEY_ROUNDS = 2048;

			crypto::CXTSBlockChiperPtr m_ptrXTSBlockChiper;
			EKeyCryptoType m_cryptoType;
			crypto::crypto_astr m_password; //set protected object with CryptProtectData
		};
	}
}