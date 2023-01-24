#include "stdafx.h"
#include "../alloc/alloc.h"

#include "MemoryStream.h"

namespace CommonLib
{
	CWriteMemoryStream::CWriteMemoryStream(std::shared_ptr<IAlloc> pAlloc) : TBase(pAlloc)
	{
		if (m_pAlloc.get() == nullptr)
			m_pAlloc = IAlloc::CreateSimpleAlloc();
	}
	CWriteMemoryStream::~CWriteMemoryStream()
	{

	}

	std::streamsize CWriteMemoryStream::WriteBytes(const byte_t* buffer, size_t size)
	{
		try
		{
			if (size > 0)
			{
				ResizeWithCapacity(size);
				::memcpy(this->m_pBuffer + m_nPos, buffer, size);
				m_nPos += size;
			}

			return size;
		}
		catch (CExcBase& exc)
		{
			exc.AddMsgT(L"Failed write bytes, size: %1", size);
			throw;
		}
	}

	std::streamsize CWriteMemoryStream::WriteInverse(const byte_t* buffer, size_t size)
	{
		try
		{
			ResizeWithCapacity(size);
			for (size_t i = 0; i < size; m_nPos++, i++)
				this->m_pBuffer[m_nPos + size - i - 1] = buffer[i];

			return size;
		}
		catch (CExcBase& exc)
		{
			exc.AddMsgT(L"Failed write bytes inverse, size: %1", size);
			throw;
		}
	}

	void  CWriteMemoryStream::Resize(size_t nSize)
	{
		try
		{
			if (m_bAttach)
				throw CExcBase(L"Stream is attached");

			if (m_nSize > nSize)
				return;

			m_nSize = nSize;
			byte_t* buffer = (byte_t*)this->m_pAlloc->Alloc(sizeof(byte_t) * m_nSize);
			 if (this->m_pBuffer)
			 {
				 memcpy(buffer, m_pBuffer, m_nSize);
				 this->m_pAlloc->Free(m_pBuffer);
				 
			 }
			 m_pBuffer = buffer;

			if (m_nPos > m_nSize)
				m_nPos = m_nSize;
		}
		catch (CExcBase& exc)
		{
			exc.AddMsg(L"Failed ResizeWithCapacity");
			throw;
		}
	
	}
	
	void  CWriteMemoryStream::ResizeWithCapacity(size_t nSize)
	{

		try
		{
			if (m_bAttach)
				throw CExcBase(L"Stream is attached");

			size_t newSize = m_nSize;
			while (m_nPos + nSize > newSize)
				newSize = size_t(newSize * 1.5) + 1;

			if (newSize > m_nSize)
			{
				m_nSize = newSize;
				byte_t* buffer = (byte_t*)this->m_pAlloc->Alloc(sizeof(byte_t) * newSize);
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
		catch (CExcBase& exc)
		{
			exc.AddMsg(L"Failed ResizeWithCapacity");
			throw;
		}

	}


	///////////////////////////////////////////
	CReadMemoryStream::CReadMemoryStream()
	{}

	CReadMemoryStream::~CReadMemoryStream()
	{}

	std::streamsize  CReadMemoryStream::ReadBytes(byte_t* dst, size_t size)
	{
		if ((this->m_nPos + size) > m_nSize)
			throw CExcBase(L"ReadMemoryStream: out of range pos: %1, read size: %2", m_nPos, size);

		::memcpy(dst, this->m_pBuffer + this->m_nPos, size);
		this->m_nPos += size;

		return size;
 
	}

	std::streamsize  CReadMemoryStream::ReadInverse(byte_t* buffer, size_t size)
	{
		if ((this->m_nPos + size) > m_nSize)
			throw CExcBase(L"ReadMemoryStream: out of range pos: %1, read size: %2", m_nPos, size);

		for (size_t i = 0; i < size; m_nPos++, i++)
			buffer[i] = this->m_pBuffer[m_nPos + size - i - 1];

		this->m_nPos += size;	 

		return size;
	}

	 

}