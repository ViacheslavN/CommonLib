#pragma once


#ifdef WIN32
	#include "WinThread.h"
#else
	#include "PosixThread.h"
#endif // WIN32


namespace CommonLib
{
	class CExcBase;

	namespace synch
	{
		class CThread
		{
			public:
				CThread(std::function<void()>&& threadFunk, astr&& threadName);
				~CThread();

				CThread(const CThread&) = delete;
				CThread& operator=(const CThread&) = delete;

				thread_id_t GetThreadId() const;
				bool IsActive() const;
				const astr& GetName() const;
				void Join();
				bool Join(int timeoutms);

				bool IsHaveException() const;
				astr GetExceptionMsg() const;
				void ThrowException() const;
				
				
				static void SetDescriptionForCurrThread(const astr& threadName);
				static thread_id_t GetCurThreadId();



			private:

				void RunThread(std::function<void()> threadFunk, astr threadName);
			private:
				std::shared_ptr<CThreadImpl> m_thread;
				astr m_name;
				std::shared_ptr<CExcBase> m_exeption;
				std::function<void()> m_threadFunk;
		};
		
	}

}