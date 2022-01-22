#include "stdafx.h"
#include "Process.h"
#include "../../str/StringEncoding.h"

namespace CommonLib
{
	namespace system
	{
		namespace win
		{
			CProcess::CProcess(HANDLE handle) : m_hProcess(handle)
			{

			}

			CProcess::~CProcess()
			{
				if (IsValid())
				{
					::CloseHandle(m_hProcess);
					m_hProcess = INVALID_HANDLE_VALUE;
				}
			}

			bool CProcess::IsValid() const
			{
				return m_hProcess == INVALID_HANDLE_VALUE;
			}

			void CProcess::IsValidExc() const
			{
				if (!IsValid())
					throw CExcBase("Process handle is invalid");
			}

			astr CProcess::GetFullImageName() const
			{
				IsValidExc();
				DWORD size = MAX_PATH;
				WCHAR name[MAX_PATH];
				BOOL success = ::QueryFullProcessImageName(m_hProcess, 0, name, &size);
				if (!success)
					throw CWinExc("Failed to call QueryFullProcessImageName");

				return StringEncoding::str_w2utf8_safe(name);
			}

		 
		}
	}
}