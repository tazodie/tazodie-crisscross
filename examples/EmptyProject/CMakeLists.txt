add_executable(EmptyProject header.cpp main.cpp)
add_precompiled_header(EmptyProject ${CMAKE_CURRENT_SOURCE_DIR}/header.h)

target_link_libraries (EmptyProject CrissCross)
