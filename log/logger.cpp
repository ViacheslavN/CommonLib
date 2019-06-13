#include "stdafx.h"
#include "logger.h"
#include "../str/str.h"

namespace CommonLib
{
	ILogger::ILogger() : m_logLevel(eInfo)
	{

	}

	ILogger::~ILogger()
	{

	}

	const char *GetMessageType(eMsgType type) const
	{

	}


	void ILogger::Msg(eMsgType type, const astr& msg)
	{
		if (m_logLevel > type)
			return;

		astr msg = str_format::StrFormatSafe();
	}

	void ILogger::Msg(eMsgType type, const astr& format, const astr& msg)
	{
		if (m_logLevel > type)
			return;




	}

	void ILogger::Msg(eMsgType type, const astr& format, const astr& msg, const astr& msg1)
	{
		if (m_logLevel > type)
			return;
	}

	void ILogger::Msg(eMsgType type, const astr& format, const astr& msg, const astr& msg1, const astr& msg2)
	{
		if (m_logLevel > type)
			return;
	}

	void ILogger::Msg(eMsgType type, const astr& format, const astr& msg, const astr& msg1, const astr& msg2, const astr& msg4)
	{
		if (m_logLevel > type)
			return;
	}

	void ILogger::Msg(eMsgType type, const astr& format, const astr& msg, const astr& msg1, const astr& msg2, const astr& msg4, const astr& msg5)
	{
		if (m_logLevel > type)
			return;
	}

	void ILogger::Msg(eMsgType type, const astr& format, const astr& msg, const astr& msg1, const astr& msg2, const astr& msg4, const astr& msg5, const astr& msg6)
	{
		if (m_logLevel > type)
			return;
	}



}