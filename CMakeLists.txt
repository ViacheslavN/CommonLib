cmake_minimum_required(VERSION 3.17)
project(CommonLib)

find_library(PTHREAD_LIBRARY pthread)
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        stdafx.cpp
		alloc/simpleAlloc.cpp

		compress/zlib/adler32.c
		compress/zlib/compress.c
		compress/zlib/crc32.c
		compress/zlib/deflate.c
		compress/zlib/gzclose.c
		compress/zlib/gzlib.c
		compress/zlib/gzread.c
		compress/zlib/gzwrite.c
		compress/zlib/infback.c
		compress/zlib/inffast.c
		compress/zlib/inflate.c
		compress/zlib/inftrees.c
		compress/zlib/trees.c
		compress/zlib/uncompr.c
		compress/zlib/ZCompressStream.cpp
		compress/zlib/ZDecompressStream.cpp
		compress/zlib/ZlibUtil.cpp
		compress/zlib/ZStream.cpp
		compress/zlib/zutil.c

	#	compress/zstd/ZstdCompressionStream.cpp
	#	compress/zstd/ZstdDecompressionStream.cpp

		exception/exc_base.cpp
		exception/PosixExc.cpp

		filesystem/File.cpp
		filesystem/PathUtils.cpp
		filesystem/FilePosix.cpp
		filesystem/filesystemPosix.cpp

		log/ConsoleLogWriter.cpp
		log/FileAsyncLogger.cpp
		log/LogFileWriterBase.cpp
		log/logger.cpp
		log/LogLinePerformer.cpp

		perf/PerfCount.cpp

		str/convertToString.cpp
		str/multibyte.cpp
		str/str.cpp
		str/StringEncoding.cpp
		str/StrUtils.cpp

		stream/BitStream.cpp
		stream/FixedBitStream.cpp
		stream/FixedMemoryStream.cpp
		stream/MemoryStream.cpp
		stream/stream.cpp
		stream/WriteBitStream.cpp

		synch/PosixThread.cpp
		synch/thread.cpp

		)
set(STATIC_LIBS
        -lpthread
        )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -fPIC -fvisibility=hidden")

add_library(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${STATIC_LIBS})
target_include_directories(${PROJECT_NAME} PRIVATE ./)


#set(SOURCE_FILES
#       Tests/TestLog/TestLog.cpp
#		Tests/TestLog/TestZlib.cpp
#        )

#set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

#add_compile_options(-pthread)
#add_executable(TestLog ${SOURCE_FILES})
#target_link_libraries(TestLog PRIVATE ${STATIC_LIBS})
#target_link_libraries(TestLog PRIVATE  CommonLib)
#target_include_directories(TestLog PRIVATE ../../../)

