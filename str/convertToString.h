#pragma once

namespace CommonLib
{

	class str_utils
	{
	public:
		static wstr WStrInt8(int8_t val);
		static wstr WStrUint8(uint8_t val);
		static wstr WStrInt16(int16_t val);
		static wstr WStrUint16(uint16_t val);
		static wstr WStrInt32(int32_t val);
		static wstr WStrUint32(uint32_t val);
		static wstr WStrInt64(int64_t val);
		static wstr WStrUint64(uint64_t val);
		static wstr WStrFloat(float val);
		static wstr WStrDouble(double val);


		static wstr WStrFrom(const wchar_t *ptrStr)
		{
			return wstr(ptrStr);
		}

		static wstr WStrFrom(const wstr& val)
		{
			return val;
		}

		static  wstr WStrFrom(const int8_t& val)
		{
			return WStrInt8(val);
		}


		static  wstr WStrFrom(const uint8_t& val)
		{
			return WStrUint8(val);
		}


		static  wstr WStrFrom(const int16_t& val)
		{
			return WStrInt16(val);
		}

		static  wstr WStrFrom(const uint16_t& val)
		{
			return WStrUint16(val);
		}


		static  wstr WStrFrom(const int32_t& val)
		{
			return WStrInt32(val);
		}


		static  wstr WStrFrom(const uint32_t& val)
		{
			return WStrUint32(val);
		}


		static  wstr WStrFrom(const int64_t& val)
		{
			return WStrInt64(val);
		}


		static  wstr WStrFrom(const uint64_t& val)
		{
			return WStrUint64(val);
		}


		static wstr WStrFrom(const float& val)
		{
			return WStrFloat(val);
		}

		static  wstr WStrFrom(const double& val)
		{
			return WStrDouble(val);
		}


		static astr AStrInt8(int8_t val);
		static astr AStrUint8(uint8_t val);
		static astr AStrInt16(int16_t val);
		static astr AStrUint16(uint16_t val);
		static astr AStrInt32(int32_t val);
		static astr AStrUint32(uint32_t val);
		static astr AStrInt64(int64_t val);
		static astr AStrUint64(uint64_t val);

		static astr AStrInt8(int8_t val, uint32_t nZero);
		static astr AStrUint8(uint8_t val, uint32_t nZero);
		static astr AStrInt16(int16_t val, uint32_t nZero);
		static astr AStrUint16(uint16_t val, uint32_t nZero);
		static astr AStrInt32(int32_t val, uint32_t nZero);
		static astr AStrUint32(uint32_t val, uint32_t nZero);
		static astr AStrInt64(int64_t val, uint32_t nZero);
		static astr AStrUint64(uint64_t val, uint32_t nZero);



		static astr AStrFloat(float val);
		static astr AStrDouble(double val);
		static astr AStrFrom(const wchar_t *ptrStr);
		static astr AStrFrom(const wstr& val);

		//template<class TVal>
		//static astr AStrTo(const TVal& val) {}

		static astr AStrFrom(const astr& val)
		{
			return val;
		}

		static  astr AStrFrom(const int8_t& val)
		{
			return AStrInt8(val);
		}

		static  astr AStrFrom(const uint8_t& val)
		{
			return AStrUint8(val);
		}


		static  astr AStrFrom(const int16_t& val)
		{
			return AStrInt16(val);
		}

		static  astr AStrFrom(const uint16_t& val)
		{
			return AStrUint16(val);
		}

		static  astr AStrFrom(const int32_t& val)
		{
			return AStrInt32(val);
		}

		static  astr AStrFrom(const int32_t& val, uint32_t nZero)
		{
			return AStrInt32(val, nZero);
		}

		static  astr AStrFrom(const uint32_t& val)
		{
			return AStrUint32(val);
		}

		static  astr AStrFrom(const uint32_t& val, uint32_t nZero)
		{
			return AStrUint32(val, nZero);
		}

		static  astr AStrFrom(const int64_t& val)
		{
			return AStrInt64(val);
		}

		static  astr AStrFrom(const uint64_t& val)
		{
			return AStrUint64(val);
		}

		static astr AStrFrom(const float& val)
		{
			return AStrFloat(val);
		}

		static  astr AStrFrom(const double& val)
		{
			return AStrDouble(val);
		}

	};

}