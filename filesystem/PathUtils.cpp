#include "stdafx.h"
#include "PathUtils.h"
#include "../str/StrUtils.h"

namespace CommonLib
{
	astr CPathUtils::FindFileName(const astr& path)
	{
		if (!path.empty())
		{
			size_t nLen = path.length();
			for (size_t i = nLen - 1; i >= 0; --i)
			{
				if (path[i] == '\\' || path[i] == '/')
					return StringUtils::Right(path, i + 1);
			}
		}

		return path;
	}

	astr CPathUtils::FindOnlyFileName(const astr& path)
	{
		astr sFileName = FindFileName(path);
		if (!sFileName.empty())
		{
			const size_t nLen = sFileName.length();
			for (size_t i = nLen - 1; i >= 0; --i)
			{
				if (sFileName[i] == '.')
					return StringUtils::Left(sFileName, i); 
			}
		}
		return sFileName;
	}

	astr CPathUtils::FindFileExtension(const astr& path)
	{
		astr sFileName = FindFileName(path);
		if (sFileName.empty())
			return astr();

		const size_t nLen =  sFileName.length();
		for (size_t i = nLen - 1; i >= 0; --i)
		{
			if (sFileName[i] == '.')
				return StringUtils::Right(sFileName, i + 1);
		}

		return astr();
	}

	astr CPathUtils::FindFilePath(const astr& fullPath)
	{
		if (!fullPath.empty())
		{
			size_t nLen =  fullPath.length();
			for (size_t i = nLen - 1; i >= 0; --i)
			{
				if (fullPath[i] == '\\' || fullPath[i] == '/')
					return	StringUtils::Left(fullPath, i + 1); 
			}
		}

		return fullPath;
	}

	wstr CPathUtils::FindFileName(const wstr& path)
	{
		if (!path.empty())
		{
			size_t nLen =  path.length();
			for (size_t i = nLen - 1; i >= 0; --i)
			{
				if (path[i] == L'\\' || path[i] == L'/')
					return StringUtils::Right(path, i + 1);
			}
		}

		return path;
	}

	wstr CPathUtils::FindOnlyFileName(const wstr& path)
	{
		wstr sFileName = FindFileName(path);
		if (!sFileName.empty())
		{
			const size_t nLen = sFileName.length();
			for (size_t i = nLen - 1; i >= 0; --i)
			{
				if (sFileName[i] == L'.')
					return StringUtils::Left(sFileName, i);
			}
		}
		return sFileName;
	}

	wstr CPathUtils::FindFileExtension(const wstr& path)
	{
		wstr sFileName = FindFileName(path);
		if (sFileName.empty())
			return wstr();

		if (sFileName.empty())
			return sFileName;

		const size_t nLen =  sFileName.length();
		for (size_t i = nLen - 1; i >= 0; --i)
		{
			if (sFileName[i] == L'.')
				return StringUtils::Right(sFileName, i + 1);
		}

		return wstr();
	}

	wstr CPathUtils::FindFilePath(const wstr& fullPath)
	{
		if (!fullPath.empty())
		{
			const size_t nLen = fullPath.length();
			for (size_t i = nLen - 1; i >= 0; --i)
			{
				if (fullPath[i] == L'\\' || fullPath[i] == L'/')
					return	StringUtils::Left(fullPath, i + 1);
			}
		}

		return fullPath;
	}

}