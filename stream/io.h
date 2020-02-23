#pragma once

namespace CommonLib
{
	namespace io
	{
		class IWrite
		{
		public:
			virtual ~IWrite() = default;
			virtual std::streamsize Write(const byte_t* dataPtr, size_t dataSize) = 0;
		};

		typedef std::shared_ptr<IWrite> TWritePtr;

		class IRead
		{
		public:
			virtual ~IRead() = default;
			virtual std::streamsize Read(byte_t* dataPtr, size_t dataSize) = 0;
		};

		typedef std::shared_ptr<IRead> TReadPtr;

		class IWriteRead : public IWrite, IRead
		{
		public:
			virtual ~IWriteRead() = default;
			virtual std::streamsize Write(const byte_t* dataPtr, size_t dataSize) = 0;
			virtual std::streamsize Read(byte_t* dataPtr, size_t dataSize) = 0;
		};

		typedef std::shared_ptr<IWriteRead> TWriteReadPtr;
	}
	


}