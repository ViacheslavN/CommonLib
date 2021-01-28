#include "stdafx.h"
#include "FixedBitStream.h"
#include "../exception/exc_base.h"
namespace CommonLib
{


	CFxBitWriteStream::CFxBitWriteStream() : TBase(IAllocPtr())
	{}

	CFxBitWriteStream::~CFxBitWriteStream()
	{}

	void CFxBitWriteStream::WriteBit(bool bBit)
	{
	
		if (m_nCurrBit > m_nBitBase)
		{
			if (m_nPos == m_nSize)
				throw CExcBase("FxBitWriteStream write bit out of range ");

			m_nPos++;
			m_nCurrBit = 0;
			m_pBuffer[m_nPos] = 0;
		}

		if (bBit)
			m_pBuffer[m_nPos] |= (1 << m_nCurrBit);

		m_nCurrBit++;

	}


	bool CFxBitWriteStream::WriteBitSafe(bool bBit)
	{
		if (m_nCurrBit > m_nBitBase)
		{
			if (m_nPos == m_nSize)
				return false;

			m_nPos++;
			m_nCurrBit = 0;
			m_pBuffer[m_nPos] = 0;
		}

		if (bBit)
			m_pBuffer[m_nPos] |= (1 << m_nCurrBit);

		m_nCurrBit++;

		return true;
	}


	void CFxBitWriteStream::Attach(TStreamPtr pStream, int32_t nPos, int32_t nSize, bool bSeek)
	{
		TBase::Attach(pStream, nPos, nSize, bSeek);

		m_pBuffer[0] = 0;
		m_nCurrBit = 0;
	}
	
	CFxBitReadStream::CFxBitReadStream( ) : TBase(IAllocPtr())
	{

	}

	CFxBitReadStream::~CFxBitReadStream() {}

	bool CFxBitReadStream::ReadBit()
	{


		bool bBit = m_pBuffer[m_nPos] & (1 << m_nCurrBit) ? true : false;
		m_nCurrBit++;

		if (m_nCurrBit > m_nBitBase)
		{
			if (m_nPos == m_nSize)
				throw CExcBase("FxBitReadStream read bit out of range ");

			m_nPos++;
			m_nCurrBit = 0;
		}

		return bBit;
	}

}