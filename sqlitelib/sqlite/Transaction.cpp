#include "stdafx.h"
#include "Transaction.h"
#include "SqliteExc.h"

namespace CommonLib
{
	namespace sqlite
	{
		namespace impl
		{
			CTransaction::CTransaction(IDatabasePtr ptrDatabase) : m_ptrDatabase(ptrDatabase)
			{

			}

			CTransaction::~CTransaction()
			{
				if (m_start)
				{
					try
					{
						m_start = false;
						RollbackImpl();
					}
					catch (std::exception& exc)
					{
						exc;
					}
				}
			}

			void CTransaction::Begin()
			{
				if(m_ptrDatabase->IsReadOnly())
					m_ptrDatabase->Execute("BEGIN");
				else
					m_ptrDatabase->Execute("BEGIN IMMEDIATE");

				m_start = true;
			}

			void CTransaction::Commit()
			{
				m_start = false;
				m_ptrDatabase->Execute("COMMIT");
			}

			void CTransaction::Rollback()
			{
				RollbackImpl();
			}

			void CTransaction::RollbackImpl()
			{
				m_start = false;
				m_ptrDatabase->Execute("ROLLBACK");
			}
		}
	}
}