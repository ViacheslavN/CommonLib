#pragma once

namespace CommonLib
{
	enum eMsgType
	{
		eTrace = 1,
		eInfo = 2,
		eWarning = 4,
		eError = 8
	};

	class IlogLineFormat
	{
	public:
		virtual void FormatLogline(const astr& msg, eMsgType type, astr& outMsg);
	};
}