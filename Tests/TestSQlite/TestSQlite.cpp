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
		CommonLib::sqlite::ITransactionPtr ptrTran = CommonLib::sqlite::ITransaction::CreateTransaction(ptrDatabase);
		ptrTran->Begin();

		ptrDatabase->Execute("CREATE TABLE testTable ( "
			" contact_id INTEGER PRIMARY KEY, "
			" first_name TEXT NOT NULL, "
			" last_name TEXT NOT NULL, "
			" email TEXT NOT NULL UNIQUE, "
			" phone TEXT NOT NULL UNIQUE) ");


		ptrTran->Commit();
	}
	catch (std::exception& exc )
	{
		std::cout << exc.what();
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
