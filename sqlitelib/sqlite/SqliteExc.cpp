#include "stdafx.h"
#include "SqliteExc.h"
#include "db/sqlite3.h"

namespace CommonLib
{
	namespace sqlite
	{
		namespace imp
		{
			CSqlitExc::CSqlitExc(int sqliteErr) : m_sqliteErr(sqliteErr)
			{
				CExcBase::AddMsg(GetErrorDesc(m_sqliteErr));
			}

			CSqlitExc::CSqlitExc(const astr& err_msg, int sqliteErr) : m_sqliteErr(sqliteErr)
			{
				CExcBase::AddMsg(err_msg);
				CExcBase::AddMsg(GetErrorDesc(sqliteErr));
			}

			CSqlitExc::~CSqlitExc()
			{

			}

			std::shared_ptr<CExcBase> CSqlitExc::Clone() const
			{

				std::shared_ptr<CExcBase> ptrExc(new CExcBase(*this));
				return ptrExc;
			}

			astr CSqlitExc::GetErrorDesc(int sqliteErr)
			{
				const char * pszError = sqlite3_errstr(sqliteErr);
				if (pszError != nullptr)
					return pszError;

				return "Unknown error";
			}
		}
	}
}