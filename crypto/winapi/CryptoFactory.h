#pragma once

#include "../crypto.h"

namespace CommonLib
{
	namespace crypto
	{
		namespace winapi
		{
			class CCryptoFactory
			{
			public:
				static IRandomGeneratorPtr CreateRandomGenerator();
				static IKeyGeneratorPtr CreateKeyGenerator();
				static IAESCipherPtr CreateAESCipher(EAESKeySize keySize, bool bPadding, CipherChainMode mode);
			};
		}
	}
}