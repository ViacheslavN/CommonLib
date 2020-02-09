#include "stdafx.h"
#include "LogLinePerformer.h"
#include "../thread/thread.h"
#include "../str/str.h"

#define  TracePrefix	 "tr "
#define  InfoPrefix		 "info "
#define  WarningPrefix	 "warn "
#define  ErrorPrefix	 "err "

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
		localtime_s(&currTm, &currTime);

		msg += "[";

		msg += str_utils::AStrFrom(currTm.tm_mday);
		msg += ".";

		msg += str_utils::AStrFrom(currTm.tm_mon);
		msg += ".";

		msg += str_utils::AStrFrom(currTm.tm_year);
		msg += " ";

		msg += str_utils::AStrFrom(currTm.tm_hour);
		msg += ":";

		msg += str_utils::AStrFrom(currTm.tm_min);
		msg += ":";

		msg += str_utils::AStrFrom(currTm.tm_sec);
		msg += ":";
		msg = "]";
	}

	void CLogFilePerformer::AddThreadID(astr& msg)
	{
		msg += "<";
		msg += str_utils::AStrFrom(thread::CThread::GetCurThreadId());
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
			outMsg += "\n";
		}
	}

}