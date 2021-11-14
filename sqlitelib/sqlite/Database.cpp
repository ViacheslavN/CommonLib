#include "stdafx.h"
#include "Database.h"
#include "SqliteExc.h"
#include "Statement.h"
#include "db/sqlite3.h"
#include "filesys/SqliteVfs.h"

namespace CommonLib
{
	namespace sqlite
	{
		IDatabasePtr IDatabase::Create(const char *pszFile, DatabaseFlags flags, crypto::IDataCipherPtr ptrDataCipher)
		{
			int mode = 0;

			if (flags & ReadOnlyMode)
				mode |= SQLITE_OPEN_READONLY;
			else
				mode |= SQLITE_OPEN_READWRITE;

			if (flags & CreateDatabase)
				mode |= SQLITE_OPEN_CREATE;

			if (flags & MultithreadMode)
				mode |= SQLITE_OPEN_FULLMUTEX;
			else
				mode |= SQLITE_OPEN_NOMUTEX;

			sqlite3* pDB = nullptr;

			if (ptrDataCipher != nullptr)
			{
				int retVal = impl::CVfs::VfsCreate(NULL, 1);
				if (retVal != SQLITE_OK)
					throw impl::CSqlitExc(retVal);
			}

			//https://www.sqlite.org/src/doc/trunk/src/test_demovfs.c
			//https://www.sqlite.org/vfs.html
			int retVal = sqlite3_open_v2(pszFile, &pDB, mode, 0);
			if (retVal != SQLITE_OK)
				throw impl::CSqlitExc(retVal);

			
			return std::shared_ptr<IDatabase>(new impl::CDatabase(pDB, flags & ReadOnlyMode ? true : false));
		}

		namespace impl
		{			

			CDatabase::CDatabase(sqlite3* pDB, bool readOnly) : m_pDB(pDB), m_readOnly(readOnly)
			{			
			}

			CDatabase::~CDatabase()
			{
				sqlite3_close(m_pDB);
			}
		 
			IStatmentPtr CDatabase::PrepareQuery(const char *pszQuery)
			{
				sqlite3_stmt* pStmt = 0;
				const int nRetVal = sqlite3_prepare_v2(m_pDB, pszQuery, -1, &pStmt, 0);
				if (nRetVal != SQLITE_OK)
					throw CSqlitExc(m_pDB, nRetVal);

				return std::shared_ptr<IStatment>(new CStatement(pStmt));
			}

			void CDatabase::Execute(const char *pszQuery)
			{
				const int nRetVal = sqlite3_exec(m_pDB, pszQuery, 0, 0, 0);
				if (nRetVal != SQLITE_OK)
					throw CSqlitExc(m_pDB, nRetVal);
	
			}

			int32_t CDatabase::GetChanges() const noexcept
			{
				return sqlite3_changes(m_pDB);
			}

			int64_t CDatabase::GetLastInsertRowID() const noexcept
			{
				return sqlite3_last_insert_rowid(m_pDB);
			}

			bool CDatabase::IsReadOnly() const noexcept
			{
				return m_readOnly;
			}
		}

	}
}