# CrissCross common makefile options.

VERSION = 0.6.5
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
GCC_MMX      := $(shell cat /proc/cpuinfo | grep mmx)
GCC_SSE      := $(shell cat /proc/cpuinfo | grep sse)
GCC_SSE2     := $(shell cat /proc/cpuinfo | grep sse2)

GCC_ISAPPLE = no
GCC_ISEMULATED = no
GCC_ISCYGMING = no
GCC_ISMINGW = no
GCC_ISINTEL = no
GCC_IS386 = no
GCC_IS486 = no
GCC_IS586 = no
GCC_IS686 = no
GCC_ISPPC = no
GCC_HAS_MMX = no
GCC_HAS_SSE = no
GCC_HAS_SSE2 = no
CC_BUILDSTATIC = yes

ifeq ($(GCC_PROC),i386)
GCC_IS386 = yes
GCC_ISINTEL = yes
endif

ifeq ($(GCC_PROC),i486)
GCC_IS486 = yes
GCC_ISINTEL = yes
endif

ifeq ($(GCC_PROC),i586)
GCC_IS586 = yes
GCC_ISINTEL = yes
endif

ifeq ($(GCC_PROC),i686)
GCC_IS686 = yes
GCC_ISINTEL = yes
endif

ifneq ($(GCC_MMX),)
GCC_HAS_MMX = yes
endif

ifneq ($(GCC_SSE),)
GCC_HAS_SSE = yes
endif

ifneq ($(GCC_SSE2),)
GCC_HAS_SSE2 = yes
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

ARCH =

ifeq ($(GCC_ISAPPLE),yes)
    ifeq ($(GCC_ISINTEL),yes)
        # Intel Core Duo or Core 2 Duo (Intel Mac)
        ARCH = -m32 -march=prescott
    endif
    ifeq ($(GCC_ISPPC),yes)
        ARCH = -mtune=G4
    endif
else
    ifeq ($(GCC_IS386),yes)
        ARCH = -m32 -march=i386
    endif
    ifeq ($(GCC_IS486),yes)
        ARCH = -m32 -march=i486
    endif
    ifeq ($(GCC_IS586),yes)
        ARCH = -m32 -march=pentium
    endif
    ifeq ($(GCC_IS686),yes)
        ARCH = -m32 -march=pentiumpro
    endif
    ifeq ($(GCC_HAS_MMX),yes)
        ARCH = -m32 -march=pentium2
    endif
    ifeq ($(GCC_HAS_MMX),yes)
        ARCH = -m32 -march=pentium2
    endif
    ifeq ($(GCC_HAS_SSE),yes)
        ARCH = -m32 -march=pentium3
    endif
    ifeq ($(GCC_MAJOR),4)
        ifeq ($(GCC_HAS_SSE2),yes)
            ARCH = -m32 -march=pentium-m -mtune=pentium-m
        endif
    endif
    ifeq ($(GCC_ISPPC),yes)
        ARCH = -mtune=G4
    endif
endif

ifeq ($(CFLAGS),)
CFLAGS = -O$(OPTLEVEL) $(ARCH) -std=c++98 -Wall -pedantic -Wno-long-long -pipe -ggdb
else
CFLAGS := -std=c++98 -Wall -pedantic -Wno-long-long
endif

ifeq ($(CXXFLAGS),)
CXXFLAGS = $(CFLAGS)
else
CXXFLAGS := -std=c++98 -Wall -pedantic -Wno-long-long
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
