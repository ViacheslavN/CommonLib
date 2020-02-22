#pragma once

namespace CommonLib
{
	class CPathUtils
	{
	public:
		static astr FindFileName(const astr& path);
		static astr FindOnlyFileName(const astr& path);
		static astr FindFileExtension(const astr& path);
		static astr FindFilePath(const astr& fullPath);

		static wstr FindFileName(const wstr& path);
		static wstr FindOnlyFileName(const wstr& path);
		static wstr FindFileExtension(const wstr& path);
		static wstr FindFilePath(const wstr& fullPath);

	};
}