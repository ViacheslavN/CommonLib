#include "stdafx.h"
#include "StreamIO.h"

namespace CommonLib
{
	CReadStreamIO::CReadStreamIO(io::TReadPtr ptrRead) : m_ptrRead(ptrRead)
	{}

	CReadStreamIO::~CReadStreamIO()
	{

	}

	std::streamsize CReadStreamIO::ReadBytes(byte_t* buffer, size_t size)
	{
		return m_ptrRead->Read(buffer, size);
	}

	std::streamsize CReadStreamIO::ReadInverse(byte_t* buffer, size_t size)
	{
		return m_ptrRead->Read(buffer, size);
	}	 


	std::streamsize CReadStreamIO::ReadBytesSafe(byte_t* buffer, size_t size)
	{
		try
		{
			return m_ptrRead->Read(buffer, size);
		}
		catch (std::exception&)
		{
			return 0;
		}

	}

	std::streamsize CReadStreamIO::ReadInverseSafe(byte_t* buffer, size_t size)
	{
		try
		{
			return m_ptrRead->Read(buffer, size);
		}
		catch (std::exception&)
		{
			return 0;
		}

	}

}