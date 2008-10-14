cmake_minimum_required (VERSION 2.6)
project (CRISSCROSS)

if(NOT WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98 -ggdb -rdynamic -Wall -Wno-long-long -pedantic")
endif(NOT WIN32)

include_directories (.)
include_directories (${CRISSCROSS_BINARY_DIR})
include_directories (${CRISSCROSS_SOURCE_DIR}/source)
link_directories (${CRISSCROSS_BINARY_DIR}/source)

add_subdirectory (source)
add_subdirectory (TestSuite)
add_subdirectory (examples)

add_custom_target (check COMMAND ${CRISSCROSS_BINARY_DIR}/TestSuite/TestSuite DEPENDS TestSuite)
