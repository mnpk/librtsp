cmake_minimum_required(VERSION 3.0)
set(PROJECT_NAME rtsp_server)
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
	
)

if(KERNELTYPE EQUAL 32)
	add_definitions(-m32)
	message(STATUS "Set `-m32` flags.")
endif()

add_executable(rtsp_server example/example_server.cpp)
target_link_libraries(
	rtsp_server
	rtsp
	${Boost_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT}
)

add_executable(rtsp_client example/example_client.cpp)
target_link_libraries(
	rtsp_client
	rtsp
	${Boost_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT}
)

add_subdirectory(rtsp)
