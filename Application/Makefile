include ../common.mk

VERSION = 0.5.0
VERSION_MAJOR = 0
ifneq ($(CC_BUILDSTATIC),yes)
LIBNAME = libcrisscross.so.$(VERSION)
MAJORLIB = libcrisscross.so.$(VERSION_MAJOR)
else
LIBNAME = libcrisscross-$(VERSION).a
endif

OBJDIR = obj/linux
OUTDIR = .
OUTNAME = criss-app.bin
OUTBIN = $(OUTNAME).$(VERSION)

SOURCES = \
main.cpp \
header.cpp

OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)

CXX = g++
CC = gcc
CCDV = ../tools/ccdv/ccdv.bin
ifneq ($(GCC_ISCYGMING),yes)
LINK = $(CXX) -rdynamic
else
LINK = $(CXX) -L../source
endif
INCLUDES = -I. -I../source -I../source/datastructures
CXXFLAGS = -O2 -Wall $(INCLUDES) -g
NM = nm
STRIP = strip

ifeq ($(GCC_MAJOR),4)
PCH = header.h.gch
endif

# all: .depend $(PCH) $(OUTDIR)/$(OUTBIN)
all: .depend $(OUTDIR)/$(OUTBIN)

clean:
	rm -rf obj
	rm -f .depend
	rm -rf .libs
	rm -f $(OUTDIR)/$(OUTBIN)
	rm -f $(OUTDIR)/$(OUTBIN).map
	rm -f $(PCH)
	
$(OUTDIR)/$(OUTBIN): $(OBJECTS)
	@echo -n "Linking... "
ifneq ($(CC_BUILDSTATIC),yes)
	@$(LINK) $+ -lpthread -lstdc++ -lcrisscross -o $(OUTDIR)/$(OUTBIN)
else
	@$(LINK) $+ -lpthread -lstdc++ -lcrisscross-$(VERSION) -o $(OUTDIR)/$(OUTBIN)
endif
	@$(NM) $(OUTDIR)/$(OUTBIN) > $(OUTDIR)/$(OUTBIN).map
	@$(STRIP) $(OUTDIR)/$(OUTBIN)
	@echo done.

$(PCH): header.h
	@$(CXX) -c header.h -o $(PCH) $(CXXFLAGS)


$(OBJDIR)/%.o: %.cpp
	@test -d $(dir $(OBJDIR)/$<) || mkdir -p $(dir $(OBJDIR)/$<)
	@$(CCDV) $(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: %.c
	@test -d $(dir $(OBJDIR)/$<) || mkdir -p $(dir $(OBJDIR)/$<)
	@$(CCDV) $(CC) $(CXXFLAGS) -c $< -o $@

.depend:
ifeq ($(GCC_ISEMULATED),yes)
	@../contrib/fastdep-0.15/fastdep $(INCLUDES) --remakedeptarget=.depend $(SOURCES) > .depend
endif

ifneq ($(MAKECMDGOALS),clean)	
-include .depend
endif

