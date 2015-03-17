cmake_minimum_required(VERSION 3.0)
set(PROJECT_NAME rtsp)
project(${PROJECT_NAME})
SET(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.57.0 COMPONENTS system thread REQUIRED)
find_package(Threads)
include_directories(
	${Boost_INCLUDE_DIRS}
)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
add_definitions(-Wall -D_REENTRANT -D_GNU_SOURCE -D_UNICODE -g -Os)
add_definitions(-std=c++1y)

set(SRCS
	connection.cpp
	connection_manager.cpp
    mime_types.cpp
	response.cpp
    request.cpp
	request_handler.cpp
	request_parser.cpp
	server.cpp
	client.cpp
)

set(EXECUTABLE_NAME ${PROJECT_NAME})
add_library(${EXECUTABLE_NAME} ${SRCS})

if(KERNELTYPE EQUAL 32)
	add_definitions(-m32)
	message(STATUS "Set `-m32` flags.")
endif()

target_link_libraries(
	${EXECUTABLE_NAME}
	${Boost_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT}
)
