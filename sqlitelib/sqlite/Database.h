#pragma once

#include "../Database.h"

struct sqlite3;

namespace CommonLib
{
	namespace sqlite
	{
		namespace impl
		{
			typedef std::shared_ptr<class CDatabase> CDatabasePtr;

			class CDatabase : public IDatabase
			{
			public:
				CDatabase(sqlite3* pDB, bool readOnly);
				virtual ~CDatabase();
 
				IStatmentPtr PrepareQuery(const char *pszQuery) override;
				void Execute(const char *pszQuery) override;
				int32_t GetChanges() const noexcept override;
				int64_t GetLastInsertRowID() const noexcept override;
				bool IsReadOnly() const noexcept override;
	
			private:
				sqlite3* m_pDB;
				bool m_readOnly;
 			};
		}
	}
}