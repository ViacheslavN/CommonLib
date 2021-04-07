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
				astr GetCommandLine() const;
				astr GetUserName() const;
				astr GetName() const;
				astr GetWindowTitle() const;



			private:
				HANDLE m_hProcess;
			};
		}
	}
}
