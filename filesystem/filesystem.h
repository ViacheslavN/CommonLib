#pragma once


#ifdef _WIN32
	#include "FileWin.h"
#else  __linux__
	//#include "FileWin.h"
#endif


namespace CommonLib
{
	class CFileUtils
	{
	public:
		static bool IsFileExist(const wstr& path);
		static void DeleteFile(const wstr& path);
		static void FileDelFolder(const wstr& path);
		static void RenameFile(const wstr& oldFile, const wstr& newFile);

		typedef std::function<bool(const wstr&)> TCheckFileObj;
		static void FileSearch(const wstr& searchMask,  const TCheckFileObj& addDir, const TCheckFileObj& addFile);
		static void FileSearch(const wstr& searchMask, wstrvec& folders, wstrvec& files);

		static bool IsFileExist(const astr& path);
		static void RenameFile(const astr& oldFile, const astr& newFile);
	};
}