#include "stdafx.h"
#include "BitStream.h"
#include "WriteBitStream.h"
#include "../exception/exc_base.h"

namespace CommonLib
{
	WriteBitStream::WriteBitStream(IAllocPtr pAlloc) : TBase(pAlloc)
	{
	}
	WriteBitStream::~WriteBitStream()
	{

	}

	void  WriteBitStream::Resize(uint32_t nSize)
	{
		try
		{
			uint32_t newSize = (uint32_t)m_nSize;

			while (m_nPos + nSize > newSize)
				newSize = uint32_t(newSize * 1.5) + 1;

			if (newSize > m_nSize)
			{
				if (m_bAttach)
					throw CExcBase("Stream is attached");

				m_nSize = newSize;
				byte_t* buffer = (byte_t*)this->m_pAlloc->Alloc(sizeof(byte_t) * newSize);
				memset(buffer, 0, newSize);

				if (this->m_pBuffer)
				{
					memcpy(buffer, this->m_pBuffer, this->m_nPos);
					if (!m_bAttach)
					{
						this->m_pAlloc->Free(m_pBuffer);
					}
				}

				this->m_pBuffer = buffer;
			}
		}
		catch (std::exception& exc)
		{
			CExcBase::RegenExc("WriteBitStream Resize", exc);
		}
 
	}

	void WriteBitStream::WriteBit(bool bBit)
	{
		try
		{
			if (m_nCurrBit > m_nBitBase)
			{
				m_nPos++;
				if (m_nPos == m_nSize)
				{
					if (m_bAttach)
						throw CExcBase("Stream is attached");

					uint32_t newSize = uint32_t(m_nSize * 1.5) + 1;
					m_nSize = newSize;

					byte_t* buffer = (byte_t*)m_pAlloc->Alloc(sizeof(byte_t) * newSize);
					if (m_pBuffer)
					{
						memcpy(buffer, m_pBuffer, m_nPos);
						if (!m_bAttach)
							m_pAlloc->Free(m_pBuffer);
					}
					m_pBuffer = buffer;

				}
				m_nCurrBit = 0;
				m_pBuffer[m_nPos] = 0;
			}
			if (bBit)
				m_pBuffer[m_nPos] |= (1 << m_nCurrBit);

			m_nCurrBit++;
		}
		catch (std::exception& exc)
		{
			CExcBase::RegenExc("WriteBitStream WriteBit", exc);
		}
	}
}