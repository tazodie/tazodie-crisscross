add_executable(SortBenchmark header.cpp main.cpp)
add_precompiled_header(SortBenchmark ${CMAKE_CURRENT_SOURCE_DIR}/header.h)

target_link_libraries (SortBenchmark CrissCross)
