#include "stdafx.h"
#include "EmptyDataCipher.h"

namespace CommonLib
{
	namespace crypto
	{
		CEmptyDataCipher::CEmptyDataCipher()
		{

		}

		CEmptyDataCipher::~CEmptyDataCipher()
		{

		}
		
		uint32_t CEmptyDataCipher::GetBufferSize(uint32_t bufDataSize)
		{
			return bufDataSize;
		}

		uint32_t CEmptyDataCipher::Encrypt(const byte_t* srcBuf, uint32_t bufSize, byte_t* dstBuf)
		{
			memcpy(dstBuf, srcBuf, bufSize);
			return bufSize;
		}

		uint32_t CEmptyDataCipher::Decrypt(const byte_t* srcBuf, uint32_t bufSize, byte_t* dstBuf)
		{
			memcpy(dstBuf, srcBuf, bufSize);
			return bufSize;
		}
	}
}