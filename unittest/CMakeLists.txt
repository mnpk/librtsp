cmake_minimum_required(VERSION 3.0)
set(PROJECT_NAME unittest)
project(${PROJECT_NAME})
SET(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.57.0 COMPONENTS system thread REQUIRED)
find_package(Threads)
include_directories(
	${Boost_INCLUDE_DIRS}
)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
add_definitions(-Wall -D_REENTRANT -D_GNU_SOURCE -D_UNICODE -g)
add_definitions(-DTIXML_USE_STL)
add_definitions(-std=c++1y)
add_definitions(--coverage)

set(SRCS
	../config/config.cpp
	../config/tinyxml/tinyxml.cpp
	../config/tinyxml/tinystr.cpp
	../config/tinyxml/tinyxmlparser.cpp
	../config/tinyxml/tinyxmlerror.cpp
    config_test.cpp
)

if(KERNELTYPE EQUAL 32)
	add_definitions(-m32)
	message(STATUS "Set `-m32` flags.")
endif()

add_executable(unittest ${SRCS})
target_link_libraries(
	unittest
	gtest_main
	gtest
	gcov
	${Boost_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT}
)
