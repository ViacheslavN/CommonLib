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

	void CWriteMemoryStream::WriteBytes(const byte_t* buffer, size_t size)
	{
		try
		{
			if (size > 0)
			{
				ResizeWithCapacity(size);
				::memcpy(this->m_pBuffer + m_nPos, buffer, size);
				m_nPos += size;
			}
		}
		catch (CExcBase& exc)
		{
			exc.AddMsgT(L"Failed write bytes, size: %1", size);
			throw;
		}
	}

	void CWriteMemoryStream::WriteInverse(const byte_t* buffer, size_t size)
	{
		try
		{
			ResizeWithCapacity(size);
			for (size_t i = 0; i < size; m_nPos++, i++)
				this->m_pBuffer[m_nPos + size - i - 1] = buffer[i];
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
				 m_pBuffer = buffer;
			 }
			 

			if (m_nPos > m_nSize)
				m_nPos = m_nSize;
		}
		catch (CExcBase& exc)
		{
			exc.AddMsg(L"Failed ResizeWithCapacity");
			throw;
		}
	
	}
	void CWriteMemoryStream::WriteStream(IStream *pStream, int64_t nPos, int64_t nSize)
	{
		IMemoryStream *pMemStream = dynamic_cast<IMemoryStream *>(pStream);
		if (pMemStream)
		{
			size_t _nPos = (nPos != -1 ? nPos : 0);
			size_t _nSize = (nSize != -1 ? nSize : pStream->Size());

			Write(_nSize);
			Write(pMemStream->Buffer() + _nPos, _nSize);
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

	void CReadMemoryStream::ReadBytes(byte_t* dst, size_t size)
	{
		if ((this->m_nPos + size) > m_nSize)
			throw CExcBase(L"ReadMemoryStream: out of range pos: %1, read size: %2", m_nPos, size);

		::memcpy(dst, this->m_pBuffer + this->m_nPos, size);
		this->m_nPos += size;
 
	}

	void CReadMemoryStream::ReadInverse(byte_t* buffer, size_t size)
	{
		if ((this->m_nPos + size) > m_nSize)
			throw CExcBase(L"ReadMemoryStream: out of range pos: %1, read size: %2", m_nPos, size);

		for (size_t i = 0; i < size; m_nPos++, i++)
			buffer[i] = this->m_pBuffer[m_nPos + size - i - 1];

		this->m_nPos += size;	 
	}

	void CReadMemoryStream::ReadStream(IStream *pStream, bool bAttach)
	{
		IMemoryStream *pMemStream = dynamic_cast<IMemoryStream *>(pStream);
		if(!pMemStream)
			throw CExcBase(L"ReadMemoryStream: can't read stream, IStream isn't MemoryStream");
		
		uint32_t nStreamSize = ReadIntu32();
		if (bAttach)
		{
			pMemStream->AttachBuffer(Buffer() + Pos(), nStreamSize);
			Seek(nStreamSize, soFromCurrent);
		}
		else
		{

			if (nStreamSize)
			{
				pMemStream->Resize(nStreamSize);
				Read(pMemStream->Buffer() + pStream->Pos(), nStreamSize);
			}
		}
	}

	bool CReadMemoryStream::ReadBytesSafe(byte_t* dst, size_t size)
	{
		if ((this->m_nPos + size) > m_nSize)
			return false;

		::memcpy(dst, this->m_pBuffer + this->m_nPos, size);
		this->m_nPos += size;

		return true;
	}

	bool CReadMemoryStream::ReadInverseSafe(byte_t* buffer, size_t size)
	{
		if ((this->m_nPos + size) > m_nSize)
			return false;

		for (size_t i = 0; i < size; m_nPos++, i++)
			buffer[i] = this->m_pBuffer[m_nPos + size - i - 1];

		this->m_nPos += size;
		return true;
	}


	bool CReadMemoryStream::ReadStreamSafe(IStream *pStream, bool bAttach)
	{
		IMemoryStream *pMemStream = dynamic_cast<IMemoryStream *>(pStream);
		if (!pMemStream)
			return false;

		uint32_t nStreamSize = ReadIntu32();
		if (bAttach)
		{
			pMemStream->AttachBuffer(Buffer() + Pos(), nStreamSize);
			try
			{
				Seek(nStreamSize, soFromCurrent);
			}
			catch (...)
			{
				return false;
			}
		}
		else
		{

			if (nStreamSize)
			{
				pMemStream->Resize(nStreamSize);
				return ReadSafe(pMemStream->Buffer() + pStream->Pos(), nStreamSize);
			}
		}

		return true;
	}

}