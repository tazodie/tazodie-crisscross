#!/bin/bash

echo "Generating build_number.h..."

if [ "$#" -lt "1" ]; then
	echo "No path specified."
	exit 1
fi

echo "Changing directory to '$1'..."
cd $1

BUILD=`svn --xml info | tr -d '\r\n' | tr -d '\n' | sed -e 's/.*<entry.*revision="\([0-9]*\)".*<\/entry>.*/\1/'`

if [ "${BUILD}x" == "x" ]; then
	echo "Build number couldn't be detected, defaulting to 1!"
	BUILD=1
else
	echo "Build number ${BUILD} detected, creating header..."
fi

PREINCLUDED="__included_build_number_h"

echo "#ifndef ${PREINCLUDED}" > build_number.h
echo "#define ${PREINCLUDED}" >> build_number.h
echo "" >> build_number.h
echo "#define BUILD_NUMBER ${BUILD}" >> build_number.h
echo "" >> build_number.h
echo "#endif" >> build_number.h
echo "" >> build_number.h
