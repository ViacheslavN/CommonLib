#pragma once
namespace CommonLib
{
	class StringUtils
	{
	public:
		static astr Left(astr str, size_t pos);
		static astr Right(astr str, size_t pos);

		static wstr Left(wstr str, size_t pos);
		static wstr Right(wstr str, size_t pos);
	};
}