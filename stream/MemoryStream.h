#pragma once

#include "stream.h"


namespace CommonLib
{
	class IAlloc;

	class CWriteMemoryStream : public TMemoryStreamBase<IWriteStreamBase>
	{
	private:

		CWriteMemoryStream(const CWriteMemoryStream& stream);
		CWriteMemoryStream& operator=(const CWriteMemoryStream& stream);
	public:
		CWriteMemoryStream(std::shared_ptr<IAlloc> pAlloc = std::shared_ptr<IAlloc>());
		~CWriteMemoryStream();

		typedef TMemoryStreamBase<IWriteStreamBase> TBase;


		virtual void WriteBytes(const byte_t* buffer, size_t size);
		virtual void WriteInverse(const byte_t* buffer, size_t size);
		virtual void WriteStream(IStream *pStream, int64_t nPos = -1, int64_t nSize = -1);
		virtual void Resize(size_t nSize);
		virtual bool IsEnoughSpace(size_t size) const { return true; }

	private:
		void  ResizeWithCapacity(size_t nSize);
	};


	class CReadMemoryStream : public TMemoryStreamBase<IReadStreamBase>
	{

	private:

		CReadMemoryStream(const CReadMemoryStream& stream);
		CReadMemoryStream& operator=(const CReadMemoryStream& stream);
	public:
		CReadMemoryStream();
		~CReadMemoryStream();

		typedef TMemoryStreamBase<IReadStreamBase> TBase;


		virtual void ReadBytes(byte_t* dst, size_t size);
		virtual void ReadInverse(byte_t* buffer, size_t size);
		virtual void ReadStream(IStream *pStream, bool bAttach);


		virtual bool ReadBytesSafe(byte_t* dst, size_t size);
		virtual bool ReadInverseSafe(byte_t* buffer, size_t size);
		virtual bool ReadStreamSafe(IStream *pStream, bool bAttach);

	};



}