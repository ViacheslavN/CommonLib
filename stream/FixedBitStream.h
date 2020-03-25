#pragma once

#include "stream.h"
#include "BitStream.h"

namespace CommonLib
{

	class FxBitWriteStream : public TBaseBitMemryStream<IWriteBitStreamBase>
	{
	public:
		typedef TBaseBitMemryStream<IWriteBitStreamBase> TBase;
		FxBitWriteStream(IAllocPtr pAlloc);
		~FxBitWriteStream();
		virtual void WriteBit(bool bBit);
		virtual void Attach(TStreamPtr pStream, int32_t nPos = -1, int32_t  nSize = -1, bool bSeek = false);
	private:


	};



	class FxBitReadStream : public TBaseBitMemryStream<IReadBitStreamBase>
	{
	public:
		typedef  TBaseBitMemryStream<IReadBitStreamBase> TBase;
		FxBitReadStream(IAllocPtr pAlloc);
		~FxBitReadStream();

		virtual bool ReadBit();
	private:


	};
}
