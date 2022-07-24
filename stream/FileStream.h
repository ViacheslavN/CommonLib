#pragma once

#include "stream.h"
#include "../filesystem/File.h"


namespace CommonLib
{




	template<class I>
	class TFileStreamBase : public I
	{


	private:

		TFileStreamBase(const TFileStreamBase& stream)  {}
		TFileStreamBase& operator=(const TFileStreamBase& stream) {}

	public:
		TFileStreamBase(file::TFilePtr ptrFile) : m_ptrFile(ptrFile)
		{}
		~TFileStreamBase()
		{}

		size_t Size() const
		{
			return m_ptrFile->GetFileSize();
		}

		void Seek(size_t position, enSeekOffset offset)
		{
			m_ptrFile->SetFilePos64(position, offset);
		}

		bool SeekSafe(size_t position, enSeekOffset offset)
		{
			try
			{
				m_ptrFile->SetFilePos64(position, offset);
				return true;
			}
			catch (...)
			{
				
			}

			return false;
			 
		}

		size_t Pos() const
		{
			return m_ptrFile->GetFilePos();
		}

		void Reset()
		{
			m_ptrFile->SetFileBegin();
		}

		void Close()
		{
			m_ptrFile->CloseFile();
		}

		void Attach(TStreamPtr pStream, int64_t nPos = -1, int64_t nSize = -1, bool bSeekPos = false)
		{
			throw CExcBase("TFileStream Deattachnot implemented");
		}

		TStreamPtr Deattach()
		{
			throw CExcBase("TFileStream Deattachnot implemented");
		}

	
	protected:
		file::TFilePtr m_ptrFile;
 	};



	class CFileReadStream : public TFileStreamBase<IReadStreamBase>
	{

	private:

		CFileReadStream(const CFileReadStream& stream);
		CFileReadStream& operator=(const CFileReadStream& stream);
	public:
		CFileReadStream(file::TFilePtr ptrFile);
		~CFileReadStream();

		typedef TFileStreamBase<IReadStreamBase> TBase;

		//Stream
		virtual size_t Size() const;
		virtual void Seek(size_t position, enSeekOffset offset);
		virtual bool SeekSafe(size_t position, enSeekOffset offset);
		virtual size_t Pos() const ;
		virtual void Reset();
		virtual void Close();
		virtual void Attach(TStreamPtr pStream, int64_t nPos, int64_t nSize, bool bSeekPos);
		virtual TStreamPtr Deattach();


		virtual void ReadBytes(byte_t* dst, size_t size);
		virtual void ReadInverse(byte_t* buffer, size_t size);
		virtual void ReadStream(IStream *pStream, bool bAttach);


		virtual bool ReadBytesSafe(byte_t* dst, size_t size);
		virtual bool ReadInverseSafe(byte_t* buffer, size_t size);
		virtual bool ReadStreamSafe(IStream *pStream, bool bAttach);
	};

	typedef std::shared_ptr<CFileReadStream> CFileReadStreamPtr;

	class CFileWriteStream : public TFileStreamBase<IWriteStreamBase>
	{

		CFileWriteStream(const CFileWriteStream& stream);
		CFileWriteStream& operator=(const CFileWriteStream& stream);

	public:
		typedef TFileStreamBase<IWriteStreamBase> TBase;

		CFileWriteStream(file::TFilePtr ptrFile);
		~CFileWriteStream();

		//Stream
		virtual size_t Size() const;
		virtual void Seek(size_t position, enSeekOffset offset);
		virtual bool SeekSafe(size_t position, enSeekOffset offset);
		virtual size_t Pos() const;
		virtual void Reset();
		virtual void Close();
		virtual void Attach(TStreamPtr pStream, int64_t nPos, int64_t nSize, bool bSeekPos);
		virtual TStreamPtr Deattach();


		virtual void WriteBytes(const byte_t* buffer, size_t size);
		virtual void WriteInverse(const byte_t* buffer, size_t size);
		virtual void WriteStream(IStream *pStream, int64_t nPos = -1, int64_t nSize = -1);
		virtual bool IsEnoughSpace(size_t size) const;
	private:
	};

	typedef std::shared_ptr<CFileWriteStream> CFileWriteStreamPtr;
}