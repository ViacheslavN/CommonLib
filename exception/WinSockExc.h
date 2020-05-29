#pragma once

#include "exc_base.h"
namespace CommonLib
{
	class CWinSockExc : public CExcBase
	{
	public:
		CWinSockExc(int err = WSAGetLastError());
 		CWinSockExc(const astr& err_msg, int err = WSAGetLastError());

		template<typename... Types>
		CWinSockExc(HRESULT err, const astr& format, Types... args) : CExcBase(format, args...), m_err(err)
		{
			CExcBase::AddMsg(GetErrorDesc(err));
		}

		~CWinSockExc() noexcept;
		virtual std::shared_ptr<CExcBase> Clone() const;

		static astr GetErrorDesc(int err);
	private:

	private:
		int m_err;

	};
}