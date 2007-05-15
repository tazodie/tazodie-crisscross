#!/bin/bash

echo "Generating build_number.h..."

if [ "$#" -lt "1" ]; then
	echo "No path specified."
	exit 1;
fi

echo "Changing directory to '$1'..."
cd $1

BUILD=`svn info | grep "Revision" | sed 's/Revision: //g'`

if [ "${BUILD}x" == "x" ]; then
	echo "Build number couldn't be detected, defaulting to 0!"
	BUILD=0
else
	echo "Build number ${BUILD} detected, creating header..."
fi

echo "#ifndef __included_build_number_h" > build_number.h
echo "#define __included_build_number_h" >> build_number.h
echo "" >> build_number.h
echo "#define BUILD_NUMBER ${BUILD}" >> build_number.h
echo "" >> build_number.h
echo "#endif" >> build_number.h
echo "" >> build_number.h
