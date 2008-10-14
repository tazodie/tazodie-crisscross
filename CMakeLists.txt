cmake_minimum_required (VERSION 2.6)
project (CRISSCROSS)

include_directories (${CRISSCROSS_SOURCE_DIR}/source)
link_directories (${CRISSCROSS_SOURCE_DIR}/source)

add_subdirectory (source)
add_subdirectory (TestSuite)
add_subdirectory (examples)

add_custom_target (check COMMAND ${CRISSCROSS_SOURCE_DIR}/TestSuite/TestSuite DEPENDS TestSuite)
