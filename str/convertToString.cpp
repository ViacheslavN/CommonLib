#include "stdafx.h"
#include "convertToString.h"
#include "StringEncoding.h"

namespace CommonLib
{
	wstr str_utils::WStrInt8(int8_t val)
	{
		return WStrInt32(int32_t(val));
	}

	wstr str_utils::WStrUint8(uint8_t val)
	{
		return WStrUint32(uint32_t(val));
	}

	wstr str_utils::WStrInt16(int16_t val)
	{
		return WStrInt32(int32_t(val));
	}

	wstr str_utils::WStrUint16(uint16_t val)
	{
		return WStrUint32(uint32_t(val));
	}

	wstr str_utils::WStrInt32(int32_t val)
	{
		wchar_t  buf[32];
#ifdef _WIN32
		swprintf_s(buf, sizeof(buf) / sizeof(wchar_t), L"%d", val);
#else
		swprintf(buf, sizeof(buf) / sizeof(wchar_t), L"%d", val);
#endif
		return buf;
	}

	wstr str_utils::WStrUint32(uint32_t val)
	{
		wchar_t  buf[32];
#ifdef _WIN32
		swprintf_s(buf, sizeof(buf) / sizeof(wchar_t), L"%u", val);
#else
		swprintf(buf, sizeof(buf) / sizeof(wchar_t), L"%u", val);
#endif
		return buf;
	}

	wstr str_utils::WStrInt64(int64_t val)
	{
		wchar_t  buf[32];
#ifdef _WIN32
		swprintf_s(buf, sizeof(buf) / sizeof(wchar_t), L"%I64d", val);
#else
		swprintf(buf, sizeof(buf) / sizeof(wchar_t), L"%I64d", val);
#endif
		return buf;
	}

	wstr str_utils::WStrUint64(uint64_t val)
	{
		wchar_t  buf[32];
#ifdef _WIN32
		swprintf_s(buf, sizeof(buf) / sizeof(wchar_t), L"%I64u", val);
#else
		swprintf(buf, sizeof(buf) / sizeof(wchar_t), L"%I64u", val);
#endif
		return buf;
	}

	wstr str_utils::WStrFloat(float val)
	{
		wchar_t  buf[32];
#ifdef _WIN32
		swprintf_s(buf, sizeof(buf) / sizeof(wchar_t), L"%.3f", val);
#else
		swprintf(buf, sizeof(buf) / sizeof(wchar_t), L"%.3f", val);
#endif
		return buf;
	}

	wstr str_utils::WStrDouble(double val)
	{
		wchar_t buf[32];
#ifdef _WIN32
		swprintf_s(buf, sizeof(buf) / sizeof(wchar_t), L"%.3lf", val);
#else
		swprintf(buf, sizeof(buf) / sizeof(wchar_t), L"%.3lf", val);
#endif
		return buf;
	}


	/////////////////////////////////////////////////////////////////////////////////////////////////



	astr str_utils::AStrInt8(int8_t val)
	{
		return AStrInt32(int32_t(val));
	}

	astr str_utils::AStrUint8(uint8_t val)
	{
		return AStrUint32(uint32_t(val));
	}

	astr str_utils::AStrInt16(int16_t val)
	{
		return AStrInt32(int32_t(val));
	}

	astr str_utils::AStrUint16(uint16_t val)
	{
		return AStrUint32(uint32_t(val));
	}


	astr str_utils::AStrInt8(int8_t val, uint32_t nZero)
	{
		return AStrInt32(int32_t(val), nZero);
	}

	astr str_utils::AStrUint8(uint8_t val, uint32_t nZero)
	{
		return AStrUint32(uint32_t(val), nZero);
	}

	astr str_utils::AStrInt16(int16_t val, uint32_t nZero)
	{
		return AStrInt32(int32_t(val), nZero);
	}

	astr str_utils::AStrUint16(uint16_t val, uint32_t nZero)
	{
		return AStrUint32(uint32_t(val), nZero);
	}

	astr str_utils::AStrInt32(int32_t val)
	{
		char  buf[32];
#ifdef _WIN32
		sprintf_s(buf, sizeof(buf), "%d", val);
#else
		snprintf(buf, sizeof(buf), "%d", val);
#endif
		return buf;
	}

	astr str_utils::AStrInt32(int32_t val, uint32_t nZero)
	{
		char  buf[32];
#ifdef _WIN32
		sprintf_s(buf, sizeof(buf), "%0*d", nZero, val);
#else
		snprintf(buf, sizeof(buf), "%0*d", nZero, val);
#endif
		return buf;
	}

	astr str_utils::AStrUint32(uint32_t val)
	{
		char  buf[32];
#ifdef _WIN32
		sprintf_s(buf, sizeof(buf), "%u", val);
#else
		snprintf(buf, sizeof(buf), "%u", val);
#endif
		return buf;
	}

	astr str_utils::AStrUint32(uint32_t val, uint32_t nZero)
	{
		char  buf[32];
#ifdef _WIN32
		sprintf_s(buf, sizeof(buf), "%0*u", nZero, val);
#else
		snprintf(buf, sizeof(buf), "%0*u", nZero, val);
#endif
		return buf;
	}

	astr str_utils::AStrInt64(int64_t val, uint32_t nZero)
	{
		char  buf[32];
#ifdef _WIN32
		sprintf_s(buf, sizeof(buf), "%0*I64d", nZero, val);
#else
		snprintf(buf, sizeof(buf), "%0*lld", nZero, val);
#endif
		return buf;
	}

	astr str_utils::AStrInt64(int64_t val)
	{
		char  buf[32];
#ifdef _WIN32
		sprintf_s(buf, sizeof(buf), "%I64d", val);
#else
		snprintf(buf, sizeof(buf), "%I64d", val);
#endif
		return buf;
	}

	astr str_utils::AStrUint64(uint64_t val)
	{
		char  buf[32];
#ifdef _WIN32
		sprintf_s(buf, sizeof(buf), "%I64u", val);
#else
		snprintf(buf, sizeof(buf), "%I64du", val);
#endif
		return buf;
	}

	astr str_utils::AStrUint64(uint64_t val, uint32_t nZero)
	{
		char  buf[32];
#ifdef _WIN32
		sprintf_s(buf, sizeof(buf), "%0*I64u", nZero, val);
#else
		snprintf(buf, sizeof(buf), "%0*llu", val);
#endif
		return buf;
	}

	astr str_utils::AStrFloat(float val)
	{
		char  buf[32];
#ifdef _WIN32
		sprintf_s(buf, sizeof(buf), "%.3f", val);
#else
		snprintf(buf, sizeof(buf), "%.3f", val);
#endif
		return buf;
	}

	astr str_utils::AStrDouble(double val)
	{
		char buf[32];
#ifdef _WIN32
		sprintf_s(buf, sizeof(buf), "%.3lf", val);
#else
		snprintf(buf, sizeof(buf), "%.3lf", val);
#endif
		return buf;
	}

	astr str_utils::AStrFrom(const wchar_t *ptrStr)
	{
		return StringEncoding::str_w2utf8_safe(ptrStr);
	}

	astr str_utils::AStrFrom(const wstr& val)
	{
		return StringEncoding::str_w2utf8_safe(val);
	}
}