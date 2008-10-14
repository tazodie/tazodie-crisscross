
include_directories (.)

add_custom_command(
	OUTPUT ${CRISSCROSS_SOURCE_DIR}/source/crisscross/build_number.h
	COMMAND ${CRISSCROSS_SOURCE_DIR}/tools/GenerateBuildNumber.sh "${CRISSCROSS_SOURCE_DIR}/source/crisscross"
)

add_custom_target(BuildNumber DEPENDS ${CRISSCROSS_SOURCE_DIR}/source/crisscross/build_number.h)

add_library(CrissCross console.cpp core_io_reader.cpp core_io_writer.cpp core_network.cpp core_socket.cpp cpuid.cpp debug.cpp error.cpp exception_handler.cpp filereader.cpp filewriter.cpp md2.cpp md4.cpp md5.cpp mutex.cpp sha1.cpp sha256.cpp sha512.cpp stopwatch.cpp system.cpp tcpsocket.cpp tiger.cpp udpsocket.cpp universal_include.cpp version.cpp)

add_dependencies(CrissCross BuildNumber)
