#pragma once

#include "stream.h"
#include "BitStream.h"

namespace CommonLib
{

	class CFxBitWriteStream : public TBaseBitMemryStream<IWriteBitStreamBase>
	{
	public:
		typedef TBaseBitMemryStream<IWriteBitStreamBase> TBase;
		CFxBitWriteStream();
		~CFxBitWriteStream();
		virtual void WriteBit(bool bBit);
		virtual bool WriteBitSafe(bool bBit);
		virtual void Attach(TStreamPtr pStream, int32_t nPos = -1, int32_t  nSize = -1, bool bSeek = false);
	private:


	};



	class CFxBitReadStream : public TBaseBitMemryStream<IReadBitStreamBase>
	{
	public:
		typedef  TBaseBitMemryStream<IReadBitStreamBase> TBase;
		CFxBitReadStream();
		~CFxBitReadStream();

		virtual bool ReadBit();
	private:


	};
}
