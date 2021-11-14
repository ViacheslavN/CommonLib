#pragma once

#include "../Database.h"

namespace CommonLib
{
	namespace sqlite
	{
		namespace impl
		{
			class CTransaction : public ITransaction
			{
			public:
				CTransaction(IDatabasePtr ptrDatabase);
				~CTransaction();

				virtual void Begin();
				virtual void Commit();
				virtual void Rollback();
			private:
				void RollbackImpl();

				IDatabasePtr m_ptrDatabase;
				bool m_start{ false };
			};
		}

		ITransactionPtr ITransaction::CreateTransaction(IDatabasePtr ptrDatabase)
		{
			return std::shared_ptr<ITransaction>(new impl::CTransaction(ptrDatabase));
		}
	}
}