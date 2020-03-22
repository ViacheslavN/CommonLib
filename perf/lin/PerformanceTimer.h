#pragma once
#pragma once
namespace CommonLib
{
	namespace lin
	{
		class CPerformanceTimer
		{
		public:
			CPerformanceTimer();
			~CPerformanceTimer();

			double GetLastedSec();
			double GetLastedMSec();
			double GetLastedUSec();
			double GetLastedNSec();
		private:
			uint64_t MeasureInterval();
			uint64_t GetNs(const struct timespec& val);
		private:
			uint64_t m_startNS{ 0 };
		};
	}
}