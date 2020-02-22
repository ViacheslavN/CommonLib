#pragma once

namespace CommonLib
{
	namespace synch
	{
		class CThreadWinImpl
		{
		public:
			CThreadWinImpl(std::function<void()>&& threadFunk);
			~CThreadWinImpl();

			bool Wait(const int Timeout = 0xFFFFFFFF) const;
			static void SetDescriptionForCurrThread(const astr& threadName);
		private:
			HANDLE m_hThread;
			std::function<void()> m_threadFunk;
 		};

		typedef CThreadWinImpl CThreadImpl;
	}
}