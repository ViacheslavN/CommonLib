#include "stdafx.h"
#include "Database.h"
#include "SqliteExc.h"
#include "Statement.h"
#include "db/sqlite3.h"
#include "filesys/SqliteVfs.h"
#include "../../str/str.h"
#include "CryptoContextHolder.h"

namespace CommonLib
{
	namespace sqlite
	{
		IDatabasePtr IDatabase::Create(const char *pszFile, uint32_t flags)
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

			if (flags & WAL)
				mode |= SQLITE_OPEN_WAL;

			sqlite3* pDB = nullptr;

			ICryptoContextPtr ptrCryptoContext = impl::CCryptoContextHolder::Instance().GetCryptoContext(pszFile);

			if (ptrCryptoContext.get() != nullptr)
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
			
			IDatabasePtr ptrDatabase  = IDatabasePtr(new impl::CDatabase(pDB, flags & ReadOnlyMode ? true : false));

			if (flags & WAL)
				ptrDatabase->Execute("PRAGMA journal_mode=WAL");

			return ptrDatabase;
		}

		namespace impl
		{			

			CDatabase::CDatabase(sqlite3* pDB, bool readOnly) : m_pDB(pDB), m_readOnly(readOnly)
			{			
			}

			CDatabase::~CDatabase()
			{
				const int nRetVal = sqlite3_close(m_pDB);
				if (nRetVal != SQLITE_OK)
				{
					//TODO log
				}
			}
		 
			IStatmentPtr CDatabase::PrepareQuery(const char *pszQuery) const
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

			bool CDatabase::IsTableExists(const char *pszTable) const
			{
				if (pszTable == nullptr)
					throw CExcBase("Invalid argument, table name is null");

				astr stm = str_format::StrFormatSafe("SELECT name FROM sqlite_master WHERE type = 'table' AND name = '%1'", pszTable);
				IStatmentPtr ptrStatemnt = PrepareQuery(stm.c_str());
				return ptrStatemnt->Next();
			}

			void CDatabase::SetBusyTimeout(int ms) noexcept
			{
				sqlite3_busy_timeout(m_pDB, ms);
			}
		}

	}
}