#pragma once

#include "../Database.h"

struct sqlite3;

namespace CommonLib
{
	namespace sqlite
	{
		namespace imp
		{
			typedef std::shared_ptr<class CDatabase> CDatabasePtr;

			class CDatabase : public IDatabase
			{
			public:
				CDatabase(sqlite3* pDB, crypto::IDataCipherPtr ptrDataCipher);
				virtual ~CDatabase();
 
				IStatmentPtr PrepareQuery(const char *pszQuery) override;
				void Execute(const char *pszQuery) override;
				int32_t GetChanges() const noexcept override;
				int64_t GetLastInsertRowID() const noexcept override;
	
			private:
				sqlite3* m_pDB;
				crypto::IDataCipherPtr m_ptrDataCipher;
			};
		}
	}
}