#pragma once
#include "../alloc/alloc.h"
#include "../exception/exc_base.h"
#include "io.h"

namespace CommonLib
{
enum enSeekOffset
{
    soFromBegin,
    soFromCurrent,
    soFromEnd,
};

class IAlloc;
class IStream;


typedef std::shared_ptr<IStream> TStreamPtr;

class IStream
{
public:
	static bool IsBigEndian()
	{
		static const uint16_t word = 0xFF00;
		return *((uint8_t*)& word) != 0;

	}
};



class IMemoryStream 
{
public:
	virtual void AttachBuffer(byte_t* pBuffer, size_t nSize, bool bCopy = false) = 0;
	virtual byte_t* DeattachBuffer() = 0;

	virtual byte_t* Buffer() = 0;
	virtual const byte_t* Buffer() const = 0;
	virtual byte_t* BufferFromCurPos() = 0;
	virtual const byte_t* BufferFromCurPos() const = 0;

	virtual void Create(size_t nSize) = 0;
	virtual void Resize(size_t nSize) = 0;

	virtual size_t Size() const = 0;
	virtual void Seek(size_t position, enSeekOffset offset) = 0;
	virtual bool SeekSafe(size_t position, enSeekOffset offset) = 0;
	virtual size_t Pos() const = 0;
	virtual void Reset() = 0;
	virtual bool IsEnoughSpace(size_t size) const = 0;
};


class IWriteStream : public io::IWrite
{
public:
	
	IWriteStream(){}
	virtual ~IWriteStream() {}

	virtual std::streamsize WriteBytes(const byte_t* buffer, size_t size) = 0;
	virtual std::streamsize WriteInverse(const byte_t* buffer, size_t size) = 0;
	virtual std::streamsize WriteDataSafe(const byte_t* buffer, size_t size);


	template <typename T>
	void WriteT(const T& value)
	{
		Write((byte_t*)&value, sizeof(T));
	}

	template <typename T>
	bool WriteTSafe(const T& value)
	{	 
		return WriteDataSafe((byte_t*)&value, sizeof(T)) != 0;
	}

	virtual void Write(bool value);
	virtual void Write(uint8_t value);
	virtual void Write(char value);
	virtual void Write(int16_t value);
	virtual void Write(uint16_t value);
	virtual void Write(uint32_t value);
	virtual void Write(int32_t value);
	virtual void Write(int64_t value);
	virtual void Write(uint64_t value);
	virtual void Write(float value);
	virtual void Write(double value);
	virtual void Write(const astr& str);
	virtual void Write(const wstr& str);
	virtual void Write(const char* pszStr);
	virtual void Write(const wchar_t* pszStr);
	virtual std::streamsize Write(const byte_t* dataPtr, size_t dataSize);

	virtual bool WriteSafe(const byte_t* pBuffer, size_t bufLen);
	virtual bool WriteSafe(bool value);
	virtual bool WriteSafe(uint8_t value);
	virtual bool WriteSafe(char value);
	virtual bool WriteSafe(int16_t value);
	virtual bool WriteSafe(uint16_t value);
	virtual bool WriteSafe(uint32_t value);
	virtual bool WriteSafe(int32_t value);
	virtual bool WriteSafe(int64_t value);
	virtual bool WriteSafe(uint64_t value);
	virtual bool WriteSafe(float value);
	virtual bool WriteSafe(double value);
	virtual bool WriteSafe(const astr& str);
	virtual bool WriteSafe(const wstr& str);
};

typedef std::shared_ptr<IWriteStream> WriteStreamPtr;


class IReadStream : public io::IRead
{
public:

	virtual ~IReadStream() {}
	IReadStream() {}

	template <typename T>
	void ReadT(T& val)
	{
		Read((byte_t*)&val, sizeof(T));
	}


	template <typename T>
	T ReadTR()
	{
		T ret;
		Read((byte_t*)&ret, sizeof(T));

		return ret;
	}


	template <typename T>
	bool SafeReadT(T& val)
	{		 
		return ReadSafe((byte_t*)&val, sizeof(T)) != 0;
	}

	virtual std::streamsize ReadBytes(byte_t* dst, size_t size) = 0;
	virtual std::streamsize ReadInverse(byte_t* buffer, size_t size) = 0;

	 


	virtual std::streamsize Read(byte_t* pBuffer, size_t bufLen);
	virtual void Read(bool& value);
	virtual void Read(char& value);
	virtual void Read(byte_t& value);
	virtual void Read(int16_t& value);
	virtual void Read(uint16_t& value);
	virtual void Read(uint32_t& value);
	virtual void Read(int32_t& value);
	virtual void Read(int64_t& value);
	virtual void Read(uint64_t& value);
	virtual void Read(float& value);
	virtual void Read(double& value);
	virtual void Read(astr& str);
	virtual void Read(wstr& str);

	virtual std::streamsize ReadSafe(byte_t* pBuffer, uint32_t bufLen);
	virtual bool ReadSafe(bool& value);
	virtual bool ReadSafe(char& value);
	virtual bool ReadSafe(byte_t& value);
	virtual bool ReadSafe(int16_t& value);
	virtual bool ReadSafe(uint16_t& value);
	virtual bool ReadSafe(uint32_t& value);
	virtual bool ReadSafe(int32_t& value);
	virtual bool ReadSafe(int64_t& value);
	virtual bool ReadSafe(uint64_t& value);
	virtual bool ReadSafe(float& value);
	virtual bool ReadSafe(double& value);
	virtual bool ReadSafe(astr& str);
	virtual bool ReadSafe(wstr& str);

	virtual bool         ReadBool();
	virtual byte_t       ReadByte();
	virtual char         ReadChar();
	virtual int16_t      Readint16();
	virtual uint16_t     Readintu16();
	virtual uint32_t     ReadDword();
	virtual int32_t      ReadInt32();
	virtual uint32_t     ReadIntu32();
	virtual int64_t      ReadInt64();
	virtual uint64_t     ReadIntu64();
	virtual float        ReadFloat();
	virtual double       ReadDouble();
	virtual astr         ReadAstr();
	virtual wstr	     ReadWstr();

};

typedef std::shared_ptr<IReadStream> ReadStreamPtr;

class IMemoryWriteStream : public IWriteStream, public IMemoryStream
{
public:

	virtual std::streamsize WriteDataSafe(const byte_t* pBuffer, size_t bufLen);

	IMemoryWriteStream() {}
	virtual ~IMemoryWriteStream() {}
};


class IMemoryReadStream : public IReadStream, public IMemoryStream
{
public:
	virtual std::streamsize ReadSafe(byte_t* pBuffer, size_t bufLen);

	IMemoryReadStream() {}
	virtual ~IMemoryReadStream() {}
};



template<class I>
class TMemoryStreamBase : public I
{

private:
	TMemoryStreamBase(const TMemoryStreamBase& stream) {}
	TMemoryStreamBase& operator=(const TMemoryStreamBase& stream) {}
public:

	TMemoryStreamBase(std::shared_ptr<IAlloc> pAlloc = std::shared_ptr<IAlloc>()) : m_pAlloc(pAlloc), m_pBuffer(0)
		, m_nPos(0)
		, m_nSize(0)
		, m_bAttach(false)
		, m_pAttachStream(NULL)

	{
		m_bIsBigEndian = IStream::IsBigEndian();

	}

	~TMemoryStreamBase()
	{
		if (!m_bAttach && m_pBuffer)
		{
			m_pAlloc->Free(m_pBuffer);
			m_pBuffer = 0;
		}
	}

	//IStream
	virtual size_t Size() const
	{
		return m_nSize;
	}

	virtual void Seek(size_t position, enSeekOffset offset)
	{
		try
		{
			if (!m_pBuffer)
				throw CExcBase(L"buffer is null", position);

			size_t newpos = 0;
			switch (offset)
			{
			case soFromBegin:
				newpos = position;
				break;
			case soFromCurrent:
				newpos = m_nPos + position;
				break;
			case soFromEnd:
				newpos = m_nSize + position;
				break;
			}
			if (newpos > m_nSize && m_bAttach)
				throw CExcBase(L"out of range  and buffer is attached pos %1 size %2", position, m_nSize);

			if (newpos > m_nSize && !m_bAttach)
			{
				Resize(newpos);
			}
			m_nPos = newpos;
		}
		catch (CExcBase& exc)
		{
			exc.AddMsgT(L"Can't seek stream pos: %1", position);
			throw;
		}
	}

	bool  SeekSafe(size_t position, enSeekOffset offset)
	{
		try
		{
			Seek( position,  offset);
		}
		catch (...)
		{
			return false;
		}

		return true;
	}
	
	virtual size_t Pos() const
	{
		return m_nPos;
	}
	
	virtual void Reset()
	{
		m_nPos = 0;
	}
	
	virtual void Close()
	{
		try
		{
			m_nPos = 0;
			m_nSize = 0;
			m_pBuffer = 0;

			if (!m_bAttach && m_pBuffer)
			{
				if (m_pAlloc.get() == nullptr)
					throw CExcBase(L"Allocator is null");

				m_pAlloc->Free(m_pBuffer);
				m_pBuffer = 0;
			}
		}
		catch (CExcBase& exc)
		{
			exc.AddMsg(L"Can't close stream");
			throw;
		}
	}


	//IMemoryStream
	virtual void AttachBuffer(byte_t* pBuffer, size_t nSize, bool bCopy = false)
	{
		try
		{
			if (bCopy)
			{
				Create(nSize);
				memcpy(m_pBuffer, pBuffer, nSize);
				m_bAttach = false;
			}
			else
			{
				m_pBuffer = pBuffer;
				m_bAttach = true;

			}
			if (m_pAttachStream)
				m_pAttachStream = NULL;

			m_nPos = 0;
			m_nSize = nSize;
		}
		catch (CExcBase& exc)
		{
			exc.AddMsg(L"Can't attach to buffer");
			throw;
		}
	}

	virtual byte_t* DeattachBuffer()
	{
		byte_t* tmp = m_pBuffer;
		m_nPos = 0;
		m_nSize = 0;
		m_pBuffer = 0;
		m_bAttach = false;
		return tmp;
	}

	virtual byte_t* Buffer()
	{
		return m_pBuffer;
	}

	virtual const byte_t* Buffer() const
	{
		return m_pBuffer;
	}

	virtual byte_t* BufferFromCurPos()
	{
		return m_pBuffer + m_nPos; 
	}

	virtual const byte_t* BufferFromCurPos() const
	{
		return m_pBuffer + m_nPos;
	}

	virtual void Create(size_t nSize)
	{
		try
		{

			if (m_pAlloc.get() == nullptr)
				throw CExcBase(L"Allocator is null");

			if (!m_bAttach && m_pBuffer)
			{
				m_pAlloc->Free(m_pBuffer);
			}

			m_pAttachStream = NULL;
			m_pBuffer = (byte_t*)m_pAlloc->Alloc(sizeof(byte_t) * nSize);
			m_nPos = 0;
			m_nSize = nSize;
			m_bAttach = false;
		}
		catch (CExcBase& exc)
		{
			exc.AddMsgT(L"Can't create stream size: %1", nSize);
			throw;
		}
	}

	virtual void Resize(size_t nSize) { throw CExcBase(L"TMemoryStreamBase: resize isn't implemented"); }
protected:

	byte_t * m_pBuffer;
	size_t  m_nPos;
	size_t   m_nSize;
	bool m_bIsBigEndian;
	std::shared_ptr<IAlloc> m_pAlloc;
	bool m_bAttach;
	TStreamPtr m_pAttachStream;
 };

 
}
