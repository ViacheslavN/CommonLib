#pragma once

#include "stream.h"


namespace CommonLib
{
	class IAlloc;

	class CFxMemoryWriteStream : public TMemoryStreamBase<IWriteStreamBase>
	{

		CFxMemoryWriteStream(const CFxMemoryWriteStream& stream);
		CFxMemoryWriteStream& operator=(const CFxMemoryWriteStream& stream);

	public:
		typedef TMemoryStreamBase<IWriteStreamBase> TBase;

		CFxMemoryWriteStream();
		~CFxMemoryWriteStream();
			

		virtual void WriteBytes(const byte_t* buffer, size_t size);
		virtual void WriteInverse(const byte_t* buffer, size_t size);
		virtual void WriteStream(IStream *pStream, int64_t nPos = -1, int64_t nSize = -1);
		virtual bool IsEnoughSpace(size_t size) const;
	};

	typedef std::shared_ptr<CFxMemoryWriteStream> CFxMemoryWriteStreamPtr;
}