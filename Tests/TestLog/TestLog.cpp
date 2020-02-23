// TestLog.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "stdafx.h"
void TestZlib();

int main()
{
	TestZlib();
	return 0;
	astr path = "C:\\dir1\\dir2\\file.ttt\\";
	wstr pathw = L"C:\\dir1\\dir2\\file.ttt\\";


	astr left = CommonLib::StringUtils::Left(path, 3);
	astr right = CommonLib::StringUtils::Right(path, 3);

	astr FileExtension = CommonLib::CPathUtils::FindFileExtension(path);
	astr FileName = CommonLib::CPathUtils::FindFileName(path);
	astr OnlyFileName = CommonLib::CPathUtils::FindOnlyFileName(path);
	astr Path = CommonLib::CPathUtils::FindFilePath(path);

	wstr FileExtensionW = CommonLib::CPathUtils::FindFileExtension(pathw);
	wstr FileNameW = CommonLib::CPathUtils::FindFileName(pathw);
	wstr OnlyFileNameW = CommonLib::CPathUtils::FindOnlyFileName(pathw);
	wstr PathW = CommonLib::CPathUtils::FindFilePath(pathw);

	std::shared_ptr<CommonLib::IlogLineFormat> plogLineFormat;
	std::shared_ptr<CommonLib::IlogRetention> plogRetention;

	std::shared_ptr<CommonLib::IlogWriter> fileLogger(new CommonLib::CFileAsyncLogger(1000, plogRetention));
	fileLogger->Open("D:\\backup.log");


	CommonLib::CLogger log;

	log.InnitLog(plogLineFormat, fileLogger);

	for (size_t i = 0; i < 100; ++i)
	{
		log.InfoT("Message %1", i);
	}

	fileLogger->Close();
	for (size_t i = 0; i < 100; ++i)
	{
		log.InfoT("Message %1", i);
	}

	fileLogger->Open("D:\\backup.log");

	
	::Sleep(2000);
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
