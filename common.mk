# CrissCross common makefile options.

VERSION = 0.7.1
VERSION_MAJOR = 0

OPTLEVEL = 3

# Define a custom CHOST here.
#CHOST = i386-pc-linux-gnu

TARGET_BITS =

ifneq ($(CHOST),)
PREFIX = $(CHOST)-
else
PREFIX =
endif

MAKEFLAGS += -rR

ifneq ($(BUILDFORNDS),1)
CXX = $(PREFIX)g++
CC = $(PREFIX)gcc
AR = ar
RANLIB = ranlib
NM = nm
STRIP = : strip
else
CXX = $(DEVKITARM)/bin/arm-eabi-g++
CC = $(DEVKITARM)/bin/arm-eabi-gcc
AR = $(DEVKITARM)/bin/arm-eabi-ar
RANLIB = $(DEVKITARM)/bin/arm-eabi-ranlib
NM = $(DEVKITARM)/bin/arm-eabi-nm
STRIP = : $(DEVKITARM)/bin/arm-eabi-strip
NDSTOOL = $(DEVKITARM)/bin/ndstool -v
TARGET_BITS =
endif

STDC = -std=c99 -pedantic
STDCPP = -std=c++98 -pedantic

LINK = $(CXX)
LDFLAGS = $(TARGET_BITS) -lstdc++ -L../source  -L../../source -lCrissCross

GCC_APPLE    := $(shell $(CXX) -v 2>&1 | \
                    grep "Apple" )
GCC_MINGW    := $(shell $(CXX) -v 2>&1 | \
                    grep "mingw" )
GCC_CYGMING  := $(shell $(CXX) -v 2>&1 | \
                    grep "cygming" )
GCC_NDS      := $(shell $(CXX) -v 2>&1 | \
                    grep "devkitARM" )
GCC_MAJOR    := $(shell $(CXX) -dumpversion 2>&1 | \
                        cut -d' ' -f3  | cut -d'.' -f1)
GCC_MINOR    := $(shell $(CXX) -dumpversion 2>&1 | \
                        cut -d' ' -f3  | cut -d'.' -f2)
GCC_PROC     := $(shell uname -m)
GCC_MMX      := $(shell cat /proc/cpuinfo 2> /dev/null | grep mmx)
GCC_SSE      := $(shell cat /proc/cpuinfo 2> /dev/null | grep sse)
GCC_SSE2     := $(shell cat /proc/cpuinfo 2> /dev/null | grep sse2)

GCC_ISAPPLE = no
GCC_ISEMULATED = no
GCC_ISCYGMING = no
GCC_ISMINGW = no
GCC_ISINTEL = no
GCC_IS386 = no
GCC_IS486 = no
GCC_IS586 = no
GCC_IS686 = no
GCC_ISX64 = no
GCC_ISPPC = no
GCC_HAS_MMX = no
GCC_HAS_SSE = no
GCC_HAS_SSE2 = no
CC_BUILDSTATIC = yes

ifeq ($(GCC_NDS),)

ifeq ($(GCC_PROC),i386)
	ifeq ($(TARGET_BITS),-m64)
		GCC_ISX64 = yes
		GCC_ISINTEL = yes
	else
		GCC_IS386 = yes
		GCC_ISINTEL = yes
	endif
endif

ifeq ($(GCC_PROC),i486)
	ifeq ($(TARGET_BITS),-m64)
		GCC_ISX64 = yes
		GCC_ISINTEL = yes
	else
		GCC_IS486 = yes
		GCC_ISINTEL = yes
	endif
endif

ifeq ($(GCC_PROC),i586)
	ifeq ($(TARGET_BITS),-m64)
		GCC_ISX64 = yes
		GCC_ISINTEL = yes
	else
		GCC_IS586 = yes
		GCC_ISINTEL = yes
	endif
endif

ifeq ($(GCC_PROC),i686)
	ifeq ($(TARGET_BITS),-m64)
		GCC_ISX64 = yes
		GCC_ISINTEL = yes
	else
		GCC_IS686 = yes
		GCC_ISINTEL = yes
	endif
endif

ifeq ($(GCC_PROC),x86_64)
GCC_ISX64 = yes
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
        ifeq ($(TARGET_BITS),-m64)
            ARCH = -march=nocona -arch x86_64
	else
	    ARCH = -march=prescott -arch i386
        endif
    endif
    ifeq ($(GCC_ISPPC),yes)
        ARCH = -mtune=G4 -arch ppc
    endif
else
    ifeq ($(GCC_IS386),yes)
        ARCH = -march=i386
    endif
    ifeq ($(GCC_IS486),yes)
        ARCH = -march=i486
    endif
    ifeq ($(GCC_IS586),yes)
        ARCH = -march=pentium
    endif
    ifeq ($(GCC_IS686),yes)
        ARCH = -march=pentiumpro
    endif
    ifeq ($(GCC_HAS_MMX),yes)
        ARCH = -march=pentium2
    endif
    ifeq ($(GCC_HAS_MMX),yes)
        ARCH = -march=pentium2
    endif
    ifeq ($(GCC_HAS_SSE),yes)
        ARCH = -march=pentium3
    endif
    ifeq ($(GCC_MAJOR),4)
        ifeq ($(GCC_HAS_SSE2),yes)
            ARCH = -march=pentium-m -mtune=pentium-m
        endif
    endif
    ifeq ($(GCC_ISPPC),yes)
        ARCH = -mtune=G4
    endif
    ifeq ($(GCC_ISX64),yes)
        ARCH = -march=nocona
    endif
endif

ifneq ($(GCC_NDS),)

ifeq ($(strip $(DEVKITARM)),)
    $(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM)
endif

STDC =
STDCPP =
# ARCH = -march=armv5te -mtune=arm946e-s -mthumb -mthumb-interwork -DARM9
ARCH = -march=armv5te -mtune=arm946e-s -DARM9
LDFLAGS += -L$(DEVKITPRO)/libnds/lib -L$(DEVKITPRO)/dswifi/lib -L$(DEVKITPRO)/libfat/nds/lib -lfat -lnds9 -specs=ds_arm9.specs -g $(ARCH) -mno-fpu
INCLUDES = -I$(DEVKITARM)/arm-eabi/include -I$(DEVKITPRO)/libnds/include -I$(DEVKITPRO)/libfat/include -I$(DEVKITPRO)/dswifi/include

include $(DEVKITARM)/ds_rules

else

LDFLAGS += -lpthread

endif

ifeq ($(CFLAGS),)
CFLAGS = -O$(OPTLEVEL) $(TARGET_BITS) $(STDC) $(ARCH) -Wall -Wno-long-long -rdynamic -pipe -ggdb
else
CFLAGS += $(STDC) -rdynamic -Wall -Wno-long-long
endif

ifeq ($(CXXFLAGS),)
CXXFLAGS = -O$(OPTLEVEL) $(TARGET_BITS) $(STDCPP) $(ARCH) -Wall -Wno-long-long -pipe -ggdb -rdynamic -fno-rtti -fno-exceptions
else
CXXFLAGS += $(STDCPP) -Wall -Wno-long-long -rdynamic -fno-rtti -fno-exceptions
endif

ifneq ($(CC_BUILDSTATIC),yes)
LIBNAME = libCrissCross-$(VERSION).so
else
LIBNAME = libCrissCross.a
endif 
