# CrissCross common makefile options.

VERSION = 0.6.0
VERSION_MAJOR = 0

ifeq ($(CXX),)
CXX = g++
endif

ifeq ($(CC),)
CC = gcc
endif

LINK = $(CXX)

ifeq ($(CFLAGS),)
CFLAGS = -O3 -march=pentium2 -mtune=pentium2 -Wall -ansi -pedantic -Wno-long-long -pipe -g
else
CFLAGS := -Wall -ansi -pedantic -Wno-long-long
endif

ifeq ($(CXXFLAGS),)
CXXFLAGS = $(CFLAGS)
else
CXXFLAGS := -Wall -ansi -pedantic -Wno-long-long
endif

INCLUDES = 

GCC_APPLE    := $(shell $(CXX) -v 2>&1 | \
                    grep "Apple" )
GCC_MINGW    := $(shell $(CXX) -v 2>&1 | \
                    grep "mingw" )
GCC_CYGMING  := $(shell $(CXX) -v 2>&1 | \
                    grep "cygming" )
GCC_MAJOR    := $(shell $(CXX) -v 2>&1 | \
                        grep " version " | cut -d' ' -f3  | cut -d'.' -f1)
GCC_MINOR    := $(shell $(CXX) -v 2>&1 | \
                        grep " version " | cut -d' ' -f3  | cut -d'.' -f2)

GCC_ISEMULATED = no
GCC_ISCYGMING = no
GCC_ISMINGW = no
CC_BUILDSTATIC = no

ifneq ($(GCC_MINGW),)
GCC_ISMINGW = yes
GCC_ISEMULATED = yes
endif

ifneq ($(GCC_APPLE),)
GCC_ISAPPLE = yes
CC_BUILDSTATIC = yes
endif

ifneq ($(GCC_CYGMING),)
GCC_ISCYGMING = yes
GCC_ISEMULATED = yes
CC_BUILDSTATIC = yes
endif

ifeq ($(GCC_ISCYGMING),yes)
FPIC =
else
FPIC = -fPIC
endif

ifneq ($(CC_BUILDSTATIC),yes)
LIBNAME = libCrissCross.so
else
LIBNAME = libCrissCross-$(VERSION).a
endif

AR = ar rc
RANLIB = ranlib
NM = nm
STRIP = :
