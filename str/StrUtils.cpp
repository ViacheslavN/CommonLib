#include "stdafx.h"
#include "StrUtils.h"

namespace CommonLib
{

	astr StringUtils::Left(astr str, size_t pos)
	{

		if (str.length() < pos || str.empty())
			return astr();

		return str.substr(0, pos);
	}

	astr StringUtils::Right(astr str, size_t pos)
	{
		if (str.length() < pos || str.empty())
			return astr();

		size_t count = str.length() - pos;
		return str.substr(pos, count);
	}

	wstr StringUtils::Left(wstr str, size_t pos)
	{
		if (str.length() < pos || str.empty())
			return wstr();

		return str.substr(0, pos);
	}

	wstr StringUtils::Right(wstr str, size_t pos)
	{
		if (str.length() < pos || str.empty())
			return wstr();

		size_t count = str.length() - pos;
		return str.substr(pos, count);
	}

}