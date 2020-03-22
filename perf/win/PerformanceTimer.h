#pragma once
namespace CommonLib
{
	namespace win
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
				double MeasureInterval();

			private:
				uint64_t m_frequency{0}; 
				uint64_t m_start{ 0 }; 
		};
	}
}