#pragma once

namespace CommonLib
{
	namespace system
	{
		namespace win
		{
			typedef std::shared_ptr<class CProcess> CProcessPtr;

			class CProcess
			{
			public:
				CProcess(HANDLE handle);
				~CProcess();

				bool IsValid() const;

				astr GetFullImageName() const;
 

			private:
				void IsValidExc() const;
			private:
				HANDLE m_hProcess;
			};
		}
	}
}
