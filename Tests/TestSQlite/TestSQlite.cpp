// TestSQlite.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "../../CommonLib.h"
#include "../../sqlitelib/Database.h"
#include "../../crypto/EmptyDataCipher.h"

int main()
{
	try
	{
		std::shared_ptr<CommonLib::crypto::IDataCipher> ptrDataCipher(new CommonLib::crypto::CEmptyDataCipher());
		CommonLib::sqlite::IDatabasePtr ptrDatabase = CommonLib::sqlite::IDatabase::Create("test.db", CommonLib::sqlite::CreateDatabase, ptrDataCipher);
		ptrDatabase->SetBusyTimeout(1000);
	

		if (ptrDatabase->IsTableExists("testTable"))
		{
			{
				CommonLib::sqlite::IStatmentPtr ptrStatment = ptrDatabase->PrepareQuery("SELECT contact_id, first_name, last_name, email, phone from testTable");
				if (ptrStatment->Next())
				{
					std::cout << ptrStatment->ReadInt32(1) << "\n";
					std::cout << ptrStatment->ReadText(2) << "\n";
					std::cout << ptrStatment->ReadText(3) << "\n";
					std::cout << ptrStatment->ReadText(4) << "\n";
					std::cout << ptrStatment->ReadText(5) << "\n";
				}
			}

			CommonLib::sqlite::ITransactionPtr ptrTran = CommonLib::sqlite::ITransaction::CreateTransaction(ptrDatabase);
			ptrTran->Begin();
			ptrDatabase->Execute("drop table testTable");
			ptrTran->Commit();
		}

		CommonLib::sqlite::ITransactionPtr ptrTran = CommonLib::sqlite::ITransaction::CreateTransaction(ptrDatabase);
		ptrTran->Begin();

		ptrDatabase->Execute("CREATE TABLE testTable ( "
			" contact_id INTEGER PRIMARY KEY, "
			" first_name TEXT NOT NULL, "
			" last_name TEXT NOT NULL, "
			" email TEXT NOT NULL UNIQUE, "
			" phone TEXT NOT NULL UNIQUE) ");

		CommonLib::sqlite::IStatmentPtr ptrStatment = ptrDatabase->PrepareQuery("INSERT INTO testTable(contact_id, first_name, last_name, email, phone) VALUES(?,?,?,?,?)");
		ptrStatment->BindInt32(1, 1);
		ptrStatment->BindText(2, "first_name", true);
		ptrStatment->BindText(3, "last_name", true);
		ptrStatment->BindText(4, "email", true);
		ptrStatment->BindText(5, "phone", true);

		ptrStatment->Next();
		ptrTran->Commit();
	}
	catch (std::exception& exc )
	{
		std::cout << "Error: " << exc.what();
	}

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file