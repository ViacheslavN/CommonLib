#include "stdafx.h"
#include "../alloc/alloc.h"
#include "FixedMemoryStream.h"

namespace CommonLib
{


	CFxMemoryWriteStream::CFxMemoryWriteStream()
	{

	}

	CFxMemoryWriteStream::~CFxMemoryWriteStream()
	{

	}

	bool CFxMemoryWriteStream::IsEnoughSpace(size_t size) const
	{
		return !((m_nPos + size) > m_nSize);
	}
		
	std::streamsize CFxMemoryWriteStream::WriteBytes(const byte_t* buffer, size_t size)
	{
		if (size > 0)
		{
			if ((this->m_nPos + size) > m_nSize)
				throw CExcBase(L"CFxMemoryWriteStream: out of range pos: %1, read size: %2", m_nPos, size);

			::memcpy(m_pBuffer + m_nPos, buffer, size);
			m_nPos += size;
		}

		return size;
	}

	std::streamsize CFxMemoryWriteStream::WriteInverse(const byte_t* buffer, size_t size)
	{
		if (size > 0)
		{
			if ((this->m_nPos + size) > m_nSize)
				throw CExcBase(L"CFxMemoryWriteStream: out of range pos: %1, read size: %2", m_nPos, size);

			for (size_t i = 0; i < size; m_nPos++, i++)
				m_pBuffer[m_nPos + size - i - 1] = buffer[i];
		}

		return size;
	}	
}