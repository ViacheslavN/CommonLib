#pragma once
#include "IDataCipher.h"

namespace CommonLib
{
	namespace crypto
	{
		class CEmptyDataCipher : public IDataCipher
		{
		public:
			CEmptyDataCipher();
			virtual ~CEmptyDataCipher();


			virtual uint32_t GetBufferSize(uint32_t bufDataSize);

			virtual uint32_t Encrypt(const byte_t* srcBuf, uint32_t bufSize, byte_t* dstBuf);
			virtual uint32_t Decrypt(const byte_t* srcBuf, uint32_t bufSize, byte_t* dstBuf);

		};
	}
}