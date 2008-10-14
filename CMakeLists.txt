cmake_minimum_required (VERSION 2.6)
project (CrissCross)

set(CMAKE_BUILD_TYPE RelWithDebInfo)

# - Try to find precompiled headers support for GCC 3.4 and 4.x
# Once done this will define:
#
# Variable:
#   PCHSupport_FOUND
#
# Macro:
#   ADD_PRECOMPILED_HEADER

IF(CMAKE_COMPILER_IS_GNUCXX)
    EXEC_PROGRAM(${CMAKE_CXX_COMPILER}
                 ARGS -dumpversion
                 OUTPUT_VARIABLE gcc_compiler_version)
#   STRING(REGEX REPLACE ".* ([0-9]\\.[0-9]\\.[0-9]) .*" "\\1" 
#          gcc_compiler_version ${_compiler_output})
#   MESSAGE("GCC Version: ${gcc_compiler_version}")
    IF(gcc_compiler_version MATCHES "4\\.[0-9]\\.[0-9]")
        SET(PCHSupport_FOUND TRUE)
    ELSE(gcc_compiler_version MATCHES "4\\.[0-9]\\.[0-9]")
        IF(gcc_compiler_version MATCHES "3\\.4\\.[0-9]")
            SET(PCHSupport_FOUND TRUE)
        ENDIF(gcc_compiler_version MATCHES "3\\.4\\.[0-9]")
    ENDIF(gcc_compiler_version MATCHES "4\\.[0-9]\\.[0-9]")
ENDIF(CMAKE_COMPILER_IS_GNUCXX)

MACRO(ADD_PRECOMPILED_HEADER _targetName _input)
    GET_FILENAME_COMPONENT(_name ${_input} NAME)
    GET_FILENAME_COMPONENT(_path ${_input} PATH)
    SET(_source "${_input}")
    SET(_outdir "${CMAKE_CURRENT_BINARY_DIR}/${_name}.gch")
    MAKE_DIRECTORY(${_outdir})
    SET(_output "${_outdir}/${CMAKE_BUILD_TYPE}.c++")
        STRING(TOUPPER "CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}" _flags_var_name)
    SET(_compile_FLAGS ${${_flags_var_name}})
    
    GET_DIRECTORY_PROPERTY(_directory_flags INCLUDE_DIRECTORIES)

	SET(_CMAKE_CURRENT_BINARY_DIR_included_before_path FALSE)
	FOREACH(item ${_directory_flags})
			IF(${item} STREQUAL ${_path} AND NOT _CMAKE_CURRENT_BINARY_DIR_included_before_path)
					MESSAGE(FATAL_ERROR 
							"This is the ADD_PRECOMPILED_HEADER macro. "
							"CMAKE_CURREN_BINARY_DIR has to mentioned at INCLUDE_DIRECTORIES's argument list before ${_path}, where ${_name} is located"
					)       
			ENDIF(${item} STREQUAL ${_path} AND NOT _CMAKE_CURRENT_BINARY_DIR_included_before_path)
	
			IF(${item} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
					SET(_CMAKE_CURRENT_BINARY_DIR_included_before_path TRUE)
			ENDIF(${item} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})

			LIST(APPEND _compile_FLAGS "-I${item}")
	ENDFOREACH(item)

	GET_DIRECTORY_PROPERTY(_directory_flags DEFINITIONS)
    LIST(APPEND _compile_FLAGS ${_directory_flags})

    SEPARATE_ARGUMENTS(_compile_FLAGS)
    #MESSAGE("_compiler_FLAGS: ${_compiler_FLAGS}")
    #message("COMMAND ${CMAKE_CXX_COMPILER}     ${_compile_FLAGS} -x c++-header -o ${_output} ${_input}")    
    ADD_CUSTOM_COMMAND(
        OUTPUT ${_output}
        COMMAND ${CMAKE_CXX_COMPILER}
           ${_compile_FLAGS}
           -I${QT_INCLUDE_DIR}
           -I${KDE3_INCLUDE_DIR}
           ${QT_DEFINITIONS}
           ${KDE3_DEFINITIONS}
           -x c++-header
           -o ${_output} ${_source}
        DEPENDS ${_source} )
    ADD_CUSTOM_TARGET(${_targetName}_gch DEPENDS ${_output})
	ADD_DEPENDENCIES(${_targetName} ${_targetName}_gch)
    SET(CMAKE_CXX_FLAGS "-include ${_name} -Winvalid-pch ${CMAKE_CXX_FLAGS}")
ENDMACRO(ADD_PRECOMPILED_HEADER)

if(NOT WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98 -ggdb -rdynamic -Wall -Wno-long-long -pedantic")
endif(NOT WIN32)

include_directories (
	${CrissCross_BINARY_DIR}
	${CrissCross_BINARY_DIR}/source
	${CrissCross_SOURCE_DIR}/source
	.)

add_subdirectory (source)
add_subdirectory (TestSuite)
add_subdirectory (examples)

add_custom_target (check COMMAND ${CrissCross_BINARY_DIR}/TestSuite/TestSuite DEPENDS TestSuite)
