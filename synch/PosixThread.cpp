#include "stdafx.h"
#include "PosixThread.h"

#ifndef WIN32 
namespace CommonLib
{
	namespace synch
	{

		extern "C"
		{

			unsigned __stdcall thread_func(void* param)
			{

				std::function<void()>* threadFunc = reinterpret_cast<std::function<void()>*>(param);
				(*threadFunc)();
				return 0;
			}

		}


		CThreadPosixImpl::CThreadPosixImpl(std::function<void()> threadFunk)
		{
			pthread_attr_t threadAttr;
			if (pthread_attr_init(&threadAttr) == -1)
			{
				 // TO DO POSIX EXC
			}

			int ret = pthread_create(&m_tid, &threadAttr,	thread_func, &threadFunk);
			if (ret != 0) {

				// TO DO POSIX EXC
			}

			if (pthread_attr_destroy(&threadAttr) == -1)
			{
				// TO DO POSIX EXC
			}
		}

		CThreadPosixImpl::~CThreadPosixImpl()
		{
			pthread_join(m_tid, NULL);
		}

		bool CThreadPosixImpl::Wait(const int Timeout) const
		{
			return (0 == pthread_join(m_tid, NULL));
		}

		void CThreadPosixImpl::SetDescriptionForCurrThread(const astr& threadName)
		{
#if ( LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,9) )
			prctl(PR_SET_NAME, threadName.c_str(), 0, 0, 0);
#endif
		}
	}
}

#endif