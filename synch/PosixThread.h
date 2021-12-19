#pragma once

#ifndef WIN32 
namespace CommonLib
{
	namespace synch
	{
		class CThreadPosixImpl
		{
		public:
			CThreadPosixImpl(std::function<void()> threadFunk);
			~CThreadPosixImpl();

			bool Wait(const int Timeout = 0xFFFFFFFF) const;
			static void SetDescriptionForCurrThread(const astr& threadName);
		private:
			pthread_t m_tid;
		};

		typedef CThreadPosixImpl CThreadImpl;
	}
}

#endif