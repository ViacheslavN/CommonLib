#include "stdafx.h"
#include "LogLinePerformer.h"
#include "../synch/thread.h"
#include "../str/str.h"

#define  TracePrefix	 "tr   "
#define  InfoPrefix		 "info "
#define  WarningPrefix	 "warn "
#define  ErrorPrefix	 "err  "

namespace CommonLib
{


	CLogFilePerformer::CLogFilePerformer()
	{

	}

	CLogFilePerformer::~CLogFilePerformer()
	{

	}

	void CLogFilePerformer::FormatLogline(const astr& msg, eMsgType type, astr& outMsg)
	{
		AddTypeMsg(type, outMsg);
		AddCurrentTime(outMsg);
		AddThreadID(outMsg);
		AddMsg(msg, outMsg);
	}

	void CLogFilePerformer::AddCurrentTime(astr& msg)
	{
		time_t  currTime;
		time(&currTime);

		tm currTm;
#ifdef _WIN32
		localtime_s(&currTm, &currTime);
#else
		localtime_r(&currTime, &currTm);
#endif

		msg += "[";

		msg += str_utils::AStrFrom(currTm.tm_mday, 2);
		msg += ".";

		msg += str_utils::AStrFrom((currTm.tm_mon + 1), 2);
		msg += ".";

		msg += str_utils::AStrFrom((1900 + currTm.tm_year), 4);
		msg += " ";

		msg += str_utils::AStrFrom(currTm.tm_hour, 2);
		msg += ":";

		msg += str_utils::AStrFrom(currTm.tm_min, 2);
		msg += ":";

		msg += str_utils::AStrFrom(currTm.tm_sec, 2);
		msg += "]";
	}

	void CLogFilePerformer::AddThreadID(astr& msg)
	{
		msg += "<";
		msg += str_utils::AStrFrom(synch::CThread::GetCurThreadId());
		msg += ">";

	}

	void CLogFilePerformer::AddTypeMsg(eMsgType type, astr& msg)
	{
		switch (type)
		{
		case CommonLib::eTrace:
			msg += TracePrefix;
			break;
		case CommonLib::eInfo:
			msg += InfoPrefix;
			break;
		case CommonLib::eWarning:
			msg += WarningPrefix;
			break;
		case CommonLib::eError:
			msg += ErrorPrefix;
			break;
		default:
			break;
		}
	}

	void CLogFilePerformer::AddMsg(const astr& msg, astr& outMsg)
	{
		if (!msg.empty())
		{
			outMsg += " ";
			outMsg += msg;
			outMsg += "\r\n";
		}
	}

}