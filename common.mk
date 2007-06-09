# CrissCross common makefile options.

VERSION = 0.6.1
VERSION_MAJOR = 0

OPTLEVEL = 3

ifeq ($(CXX),)
CXX = g++
endif

ifeq ($(CC),)
CC = gcc
endif

LINK = $(CXX)

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
GCC_PROC     := $(shell uname -m)

GCC_ISAPPLE = no
GCC_ISEMULATED = no
GCC_ISCYGMING = no
GCC_ISMINGW = no
GCC_ISX86 = no
GCC_ISPPC = no
CC_BUILDSTATIC = yes

ifeq ($(GCC_PROC),i386)
GCC_ISX86 = yes
endif

ifeq ($(GCC_PROC),ppc)
GCC_ISPPC = yes
endif

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

ifeq ($(GCC_ISAPPLE),yes)
    ifeq ($(GCC_ISX86),yes)
        # Intel Core Duo or Core 2 Duo (Intel Mac)
        ARCH = -march=prescott -mtune=prescott
    else
    ifeq ($(GCC_ISPPC),yes)
        ARCH = -mtune=g4
    endif
    endif
else
    ifeq ($(GCC_ISX86),yes)
        ARCH = -march=pentium2 -mtune=pentium2
    else
        ARCH =
    endif
endif

ifeq ($(CFLAGS),)
CFLAGS = -O$(OPTLEVEL) $(ARCH) -Wall -ansi -pedantic -Wno-long-long -pipe -ggdb
else
CFLAGS := -Wall -ansi -pedantic -Wno-long-long
endif

ifeq ($(CXXFLAGS),)
CXXFLAGS = $(CFLAGS)
else
CXXFLAGS := -Wall -ansi -pedantic -Wno-long-long
endif

ifneq ($(CC_BUILDSTATIC),yes)
LIBNAME = libCrissCross-$(VERSION).so
else
LIBNAME = libCrissCross.a
endif

AR = ar rc
RANLIB = ranlib
NM = nm
STRIP = :
