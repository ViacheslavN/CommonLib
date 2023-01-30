#include "stdafx.h"
#include "DateUtil.h"

namespace CommonLib
{
	namespace dateutil
	{
		uint64_t CDateUtil::GetCurrentDateTime()
		{
			time_t  currTime;
			time(&currTime);

			tm currTm;
#ifdef _WIN32
			localtime_s(&currTm, &currTime);
#else 
			localtime_r(&currTime, &currTm);
#endif
			 
			uint64_t date = uint64_t(1900 + currTm.tm_year) * 10000000000 + (uint64_t)currTm.tm_mday * 100000000 + (uint64_t)(currTm.tm_mon + 1) * 1000000;			
			uint64_t time = currTm.tm_hour * 10000 + currTm.tm_min * 100 + currTm.tm_sec;
	 
			return date + time;

		}
	}
}