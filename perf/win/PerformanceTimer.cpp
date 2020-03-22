#include "stdafx.h"
#include "PerformanceTimer.h"

namespace CommonLib
{
	namespace win
	{
		CPerformanceTimer::CPerformanceTimer()
		{
			LARGE_INTEGER value;
			QueryPerformanceCounter(&value);
			m_start = uint64_t(value.QuadPart);

			QueryPerformanceFrequency(&value);
			m_frequency = uint64_t(value.QuadPart);
		}

		CPerformanceTimer::~CPerformanceTimer()
		{

		}

		double CPerformanceTimer::MeasureInterval()
		{
			LARGE_INTEGER value;
			QueryPerformanceCounter(&value);

			double intervalInSec = (double(value.QuadPart) - double(m_start)) / double(m_frequency);
			m_start = uint64_t(value.QuadPart);

			return intervalInSec;
		}

		double CPerformanceTimer::GetLastedSec()
		{
			return MeasureInterval();
		}

		double CPerformanceTimer::GetLastedMSec()
		{
			return MeasureInterval()*1000.0;
		}

		double CPerformanceTimer::GetLastedUSec()
		{
			return MeasureInterval() * 1000000.0;
		}

		double CPerformanceTimer::GetLastedNSec()
		{
			return MeasureInterval() * 1000000000.0;
		}
	}
}