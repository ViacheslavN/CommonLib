cmake_minimum_required(VERSION 3.5)
project(TestLog)

find_library(PTHREAD_LIBRARY pthread)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -fPIC -fvisibility=hidden  -pthread")

set(STATIC_LIBS
        -lpthread
        )


set(SOURCE_FILES
      TestLog.cpp
	  TestZlib.cpp
      )

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")


add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${STATIC_LIBS})
target_link_libraries(${PROJECT_NAME} PRIVATE CommonLib)
target_link_libraries(${PROJECT_NAME} PRIVATE -L${CMAKE_SOURCE_DIR}/../../)
target_include_directories(${PROJECT_NAME} PRIVATE ../../../)

 
