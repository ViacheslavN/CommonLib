#include "stdafx.h"
#include "logger.h"
#include "../str/str.h"
#include "LogLinePerformer.h"
#include "../exception/exc_base.h"


namespace CommonLib
{
	ILogger::ILogger(std::shared_ptr<IlogLineFormat>& pLogLineFormat) :
		m_logLevel(eInfo)
		, m_pLogLineFormat(pLogLineFormat)
	{
		if (m_pLogLineFormat.get() == nullptr)
			m_pLogLineFormat.reset(new CLogFilePerformer());
	}

	ILogger::~ILogger()
	{

	}



	void ILogger::Msg(eMsgType type, const astr& msg)
	{
		if (m_logLevel > type)
			return;

		astr outMsg;
		m_pLogLineFormat->FormatLogline(msg, type, outMsg);
		MessageStr(outMsg.c_str());
	}

	void ILogger::Msg(eMsgType type, const astr& format, const astr& msg)
	{
		if (m_logLevel > type)
			return;

		Msg(type, str_format::StrFormatSafe(format, msg));
	}

	void ILogger::Msg(eMsgType type, const astr& format, const astr& msg, const astr& msg1)
	{
		if (m_logLevel > type)
			return;

		Msg(type, str_format::StrFormatSafe(format, msg, msg1));
	}

	void ILogger::Msg(eMsgType type, const astr& format, const astr& msg, const astr& msg1, const astr& msg2)
	{
		if (m_logLevel > type)
			return;

		Msg(type, str_format::StrFormatSafe(format, msg, msg1, msg2));
	}

	void ILogger::Msg(eMsgType type, const astr& format, const astr& msg, const astr& msg1, const astr& msg2, const astr& msg3)
	{
		if (m_logLevel > type)
			return;

		Msg(type, str_format::StrFormatSafe(format, msg, msg1, msg2, msg3));
	}

	void ILogger::Msg(eMsgType type, const astr& format, const astr& msg, const astr& msg1, const astr& msg2, const astr& msg3, const astr& msg4)
	{
		if (m_logLevel > type)
			return;

		Msg(type, str_format::StrFormatSafe(format, msg, msg1, msg2, msg3, msg4));
	}

	void ILogger::Msg(eMsgType type, const astr& format, const astr& msg, const astr& msg1, const astr& msg2, const astr& msg3, const astr& msg4, const astr& msg5)
	{
		if (m_logLevel > type)
			return;

		Msg(type, str_format::StrFormatSafe(format, msg, msg1, msg2, msg3, msg4, msg5));
	}


	void ILogger::Trace(const astr& msg)
	{
		Msg(eTrace, msg);
	}

	void ILogger::Trace(const astr& format, const astr& msg)
	{
		Msg(eTrace, format, msg);
	}

	void ILogger::Trace(const astr& format, const astr& msg, const astr& msg1)
	{
		Msg(eTrace, format, msg, msg1);
	}

	void ILogger::Trace(const astr& format, const astr& msg, const astr& msg1, const astr& msg2)
	{
		Msg(eTrace, format, msg, msg1, msg2);
	}

	void ILogger::Trace(const astr& format, const astr& msg, const astr& msg1, const astr& msg2, const astr& msg3)
	{
		Msg(eTrace, format, msg, msg1, msg2, msg3);
	}

	void ILogger::Trace(const astr& format, const astr& msg, const astr& msg1, const astr& msg2, const astr& msg3, const astr& msg4)
	{
		Msg(eTrace, format, msg, msg1, msg2, msg3, msg4);
	}

	void ILogger::Trace(const astr& format, const astr& msg, const astr& msg1, const astr& msg2, const astr& msg3, const astr& msg4, const astr& msg5)
	{
		Msg(eTrace, format, msg, msg1, msg2, msg3, msg4, msg5);
	}

	void ILogger::Info(const astr& msg)
	{
		Msg(eInfo, msg);
	}

	void ILogger::Info(const astr& format, const astr& msg)
	{
		Msg(eInfo, format, msg);
	}

	void ILogger::Info(const astr& format, const astr& msg, const astr& msg1)
	{
		Msg(eInfo, format, msg, msg1);
	}

	void ILogger::Info(const astr& format, const astr& msg, const astr& msg1, const astr& msg2)
	{
		Msg(eInfo, format, msg, msg1, msg2);
	}

	void ILogger::Info(const astr& format, const astr& msg, const astr& msg1, const astr& msg2, const astr& msg3)
	{
		Msg(eInfo, format, msg, msg1, msg2, msg3);
	}

	void ILogger::Info(const astr& format, const astr& msg, const astr& msg1, const astr& msg2, const astr& msg3, const astr& msg4)
	{
		Msg(eInfo, format, msg, msg1, msg2, msg3, msg4);
	}

	void ILogger::Info(const astr& format, const astr& msg, const astr& msg1, const astr& msg2, const astr& msg3, const astr& msg4, const astr& msg5)
	{
		Msg(eInfo, format, msg, msg1, msg2, msg3, msg4, msg5);
	}

	void ILogger::Error(const astr& msg)
	{
		Msg(eError, msg);
	}

	void ILogger::Error(const astr& format, const astr& msg)
	{
		Msg(eError, format, msg);
	}

	void ILogger::Error(const astr& format, const astr& msg, const astr& msg1)
	{
		Msg(eError, format, msg, msg1);
	}

	void ILogger::Error(const astr& format, const astr& msg, const astr& msg1, const astr& msg2)
	{
		Msg(eError, format, msg, msg1, msg2);
	}

	void ILogger::Error(const astr& format, const astr& msg, const astr& msg1, const astr& msg2, const astr& msg3)
	{
		Msg(eError, format, msg, msg1, msg2, msg3);
	}

	void ILogger::Error(const astr& format, const astr& msg, const astr& msg1, const astr& msg2, const astr& msg3, const astr& msg4)
	{
		Msg(eError, format, msg, msg1, msg2, msg3, msg4);
	}

	void ILogger::Error(const astr& format, const astr& msg, const astr& msg1, const astr& msg2, const astr& msg3, const astr& msg4, const astr& msg5)
	{
		Msg(eError, format, msg, msg1, msg2, msg3, msg4, msg5);
	}

	void ILogger::Warning(const astr& msg)
	{
		Msg(eWarning, msg);
	}

	void ILogger::Warning(const astr& format, const astr& msg)
	{
		Msg(eWarning, format, msg);
	}

	void ILogger::Warning(const astr& format, const astr& msg, const astr& msg1)
	{
		Msg(eWarning, format, msg, msg1);
	}

	void ILogger::Warning(const astr& format, const astr& msg, const astr& msg1, const astr& msg2)
	{
		Msg(eWarning, format, msg, msg1, msg2);
	}

	void ILogger::Warning(const astr& format, const astr& msg, const astr& msg1, const astr& msg2, const astr& msg3)
	{
		Msg(eWarning, format, msg, msg1, msg2, msg3);
	}

	void ILogger::Warning(const astr& format, const astr& msg, const astr& msg1, const astr& msg2, const astr& msg3, const astr& msg4)
	{
		Msg(eWarning, format, msg, msg1, msg2, msg3, msg4);
	}

	void ILogger::Warning(const astr& format, const astr& msg, const astr& msg1, const astr& msg2, const astr& msg3, const astr& msg4, const astr& msg5)
	{
		Msg(eWarning, format, msg, msg1, msg2, msg3, msg4, msg5);
	}

	void ILogger::Exc(const std::exception& exc)
	{
		Msg(eError, str_format::StrFormatSafe("exc: %1", CExcBase::GetErrorDesc(exc)));
	}
 }