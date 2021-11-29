#pragma once
#include "../CryptoAlgoritmProvider.h"
#include "../SymmetricKey.h"

namespace CommonLib
{
	namespace crypto
	{
		namespace winapi
		{
			class CAESCipher : public IAESCipher
			{
			public:
				CAESCipher(EAESKeySize keySize, bool bPadding, CipherChainMode mode);
				virtual ~CAESCipher();

				virtual uint32_t GetKeySize() const;
				virtual void SetKey(const crypto_vector& keyData);

				virtual uint32_t GetIVSize() const;
				virtual byte_t* GetIVData();
				virtual const byte_t* GetIVData() const;

				virtual uint32_t GetBufferSize(uint32_t bufDataSize);
				virtual uint32_t GetBlockSize() const;
				virtual uint32_t Encrypt(const byte_t* srcBuf, uint32_t bufSize, byte_t* dstBuf, uint32_t dstSize);
				virtual uint32_t Decrypt(const byte_t* srcBuf, uint32_t bufSize, byte_t* dstBuf, uint32_t dstSize);
				virtual uint32_t Encrypt(byte_t* srcBuf, uint32_t bufSize);
				virtual uint32_t Decrypt(byte_t* srcBuf, uint32_t bufSize);
			private:
				void SetChainMode(CipherChainMode mode);
			private:
				CBcryptAlgProviderPtr m_ptrAlgProvider;
				CSymmetricKeyPtr m_ptrKey;
				bool m_bPadding;
				uint32_t m_nBlockSize;
				uint32_t m_nObjectSize;
				EAESKeySize m_keySize;
				CipherChainMode m_chainMode;
				crypto_vector m_IvData;
			};
		}
	}
}