#include "stdafx.h"
#include "CryptoFactory.h"
#include "random/RandomGenerator.h"
#include "KeyGenerator.h"
#include "aes/AESCipher.h"

namespace CommonLib
{
	namespace crypto
	{
		namespace winapi
		{
			IRandomGeneratorPtr CCryptoFactory::CreateRandomGenerator()
			{
				return IRandomGeneratorPtr(new CRandomGenerator());
			}

			IKeyGeneratorPtr CCryptoFactory::CreateKeyGenerator()
			{
				return IKeyGeneratorPtr(new CKeyGenerator());
			}

			IAESCipherPtr CCryptoFactory::CreateAESCipher(EAESKeySize keySize, bool bPadding, CipherChainMode mode)
			{ 
				return IAESCipherPtr(new CAESCipher(keySize, bPadding, mode));
			}
		}
	}
}