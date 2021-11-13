#pragma once
namespace CommonLib
{
	namespace crypto
	{
		typedef std::shared_ptr<class IDataCipher> IDataCipherPtr;

		class IDataCipher
		{
		public:
			IDataCipher(){}
			virtual ~IDataCipher() {}


			virtual uint32_t GetBufferSize(uint32_t bufDataSize) = 0;

			virtual uint32_t Encrypt(const byte_t* srcBuf, uint32_t bufSize, byte_t* dstBuf) = 0;
			virtual uint32_t Decrypt(const byte_t* srcBuf, uint32_t bufSize, byte_t* dstBuf) = 0;


		};
	}
}