add_executable(SimpleTCPClient header.cpp main.cpp)
add_precompiled_header(SimpleTCPClient ${CMAKE_CURRENT_SOURCE_DIR}/header.h)

target_link_libraries (SimpleTCPClient CrissCross)
