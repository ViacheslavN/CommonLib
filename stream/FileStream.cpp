#include "stdafx.h"
#include "FileStream.h"


namespace CommonLib
{

	CFileReadStream::CFileReadStream(file::TFilePtr ptrFile) : TBase(ptrFile)
	{}

	CFileReadStream::~CFileReadStream()
	{}

	//Stream
	size_t CFileReadStream::Size() const
	{
		return TBase::Size();
	}

	void CFileReadStream::Seek(size_t position, enSeekOffset offset)
	{
		TBase::Seek(position, offset);
	}

	bool CFileReadStream::SeekSafe(size_t position, enSeekOffset offset)
	{
		return TBase::SeekSafe(position, offset);
	}

	size_t CFileReadStream::Pos() const
	{
		return TBase::Pos();
	}

	void CFileReadStream::Reset()
	{
		TBase::Reset();
	}

	void CFileReadStream::Close()
	{
		TBase::Close();
	}

	void CFileReadStream::Attach(TStreamPtr pStream, int64_t nPos, int64_t nSize, bool bSeekPos)
	{
		TBase::Attach(pStream, nPos, nSize, bSeekPos);
	}

	TStreamPtr CFileReadStream::Deattach()
	{
		return TBase::Deattach();
	}

	void CFileReadStream::ReadBytes(byte_t* dst, size_t size)
	{
		std::streamsize readSize = m_ptrFile->Read(dst, size);
		if(readSize != size)
			throw CExcBase("FileReadStream bytes to read %1, result %2", size, readSize);
	}

	void CFileReadStream::ReadInverse(byte_t* buffer, size_t size)
	{
		std::streamsize readSize = m_ptrFile->Read(buffer, size); //TO DO inverse
		if (readSize != size)
			throw CExcBase("FileReadStream bytes to read %1, result %2", size, readSize);
	}

	void CFileReadStream::ReadStream(IStream *pStream, bool bAttach)
	{
		if (IMemoryStream *pMemStream = dynamic_cast<IMemoryStream *>(pStream))
		{


			uint32_t nStreamSize = ReadIntu32();
			if (nStreamSize)
			{
				pMemStream->Resize(nStreamSize);
				Read(pMemStream->Buffer() + pStream->Pos(), nStreamSize);
			}
		}
		else
			throw CExcBase("CFileReadStream ReadStream, stream isn't memory stream");
	}


	bool CFileReadStream::ReadBytesSafe(byte_t* dst, size_t size)
	{
		try
		{
			std::streamsize readSize = m_ptrFile->Read(dst, size);
			return readSize == size;
		}
		catch (...)
		{
		}
		return false;
	}

	bool CFileReadStream::ReadInverseSafe(byte_t* buffer, size_t size)
	{
		try
		{
			std::streamsize readSize = m_ptrFile->Read(buffer, size);
			return readSize == size;
		}
		catch (...)
		{
		}
		return false;
	}

	bool CFileReadStream::ReadStreamSafe(IStream *pStream, bool bAttach)
	{
		try
		{
			ReadStream(pStream, bAttach);
		}
		catch (...)
		{
		}
		return false;
	}




	CFileWriteStream::CFileWriteStream(file::TFilePtr ptrFile) : TBase(ptrFile)
	{}

	CFileWriteStream::~CFileWriteStream()
	{}

	//Stream
	size_t CFileWriteStream::Size() const
	{
		return TBase::Size();
	}

	void CFileWriteStream::Seek(size_t position, enSeekOffset offset)
	{
		TBase::Seek(position, offset);
	}

	bool CFileWriteStream::SeekSafe(size_t position, enSeekOffset offset)
	{
		return TBase::SeekSafe(position, offset);
	}

	size_t CFileWriteStream::Pos() const
	{
		return TBase::Pos();
	}

	void CFileWriteStream::Reset()
	{
		TBase::Reset();
	}

	void CFileWriteStream::Close()
	{
		TBase::Close();
	}

	void CFileWriteStream::Attach(TStreamPtr pStream, int64_t nPos, int64_t nSize, bool bSeekPos)
	{
		TBase::Attach(pStream, nPos, nSize, bSeekPos);
	}

	TStreamPtr CFileWriteStream::Deattach()
	{
		return TBase::Deattach();
	}

	void CFileWriteStream::WriteBytes(const byte_t* buffer, size_t size)
	{
		this->m_ptrFile->Write(buffer, size);
	}

	void CFileWriteStream::WriteInverse(const byte_t* buffer, size_t size)
	{
		this->m_ptrFile->Write(buffer, size); //TO DO do inverse
	}

	void CFileWriteStream::WriteStream(IStream *pStream, int64_t nPos, int64_t nSize)
	{
		if (IMemoryStream *pMemStream = dynamic_cast<IMemoryStream *>(pStream))
		{
			int64_t _nPos = (nPos != -1 ? nPos : 0);
			uint32_t _nSize =(uint32_t)(nSize != -1 ? nSize : pStream->Size());

			Write(_nSize);
			Write(pMemStream->Buffer() + _nPos, _nSize);
		}
		else
			throw CExcBase("CFileWriteStream WriteStream, stream isn't memory stream");
	}

	bool CFileWriteStream::IsEnoughSpace(size_t size) const
	{
		return true;
	}
}