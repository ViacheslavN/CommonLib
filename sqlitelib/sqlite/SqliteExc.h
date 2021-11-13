#pragma once

#include "../../exception/exc_base.h"

namespace CommonLib
{
	namespace sqlite
	{
		namespace imp
		{
			class CSqlitExc : public CExcBase
			{
			public:
				CSqlitExc(int sqliteErr);
				CSqlitExc(const astr& err_msg, int sqliteErr);

				template<typename... Types>
				CSqlitExc(int sqliteErr, const astr& format, Types... args) : CExcBase(format, args...), m_sqliteErr(sqliteErr)
				{
					CExcBase::AddMsg(GetErrorDesc(sqliteErr));
				}

				~CSqlitExc() noexcept;
				virtual std::shared_ptr<CExcBase> Clone() const;

				static astr GetErrorDesc(int sqliteErr);
			private:
				int m_sqliteErr;
			};
		}
	}
}