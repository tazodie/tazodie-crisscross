GCC_MAJOR    := $(shell $(CXX) -v 2>&1 | \
                        grep " version " | cut -d' ' -f3  | cut -d'.' -f1)
GCC_MINOR    := $(shell $(CXX) -v 2>&1 | \
                        grep " version " | cut -d' ' -f3  | cut -d'.' -f2)

VERSION = 0.5.0
VERSION_MAJOR = 0
LIBNAME = libcrisscross.so.$(VERSION)
MAJORLIB = libcrisscross.so.$(VERSION_MAJOR)

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
LINK = $(CXX) -rdynamic
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
	rm -f $(LIBNAME)
	rm -f $(MAJORLIB)
	
$(OUTDIR)/$(OUTBIN): $(OBJECTS)
	@echo -n "Linking... "
	@$(LINK) $+ -lpthread -lstdc++ -lcrisscross -o $(OUTDIR)/$(OUTBIN)
	@$(NM) $(OUTDIR)/$(OUTBIN) > $(OUTDIR)/$(OUTBIN).map
	@$(STRIP) $(OUTDIR)/$(OUTBIN)
	@ln -sf ../source/$(LIBNAME)
	@ln -sf ../source/$(LIBNAME) $(MAJORLIB)
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
#	@echo Generating dependency information...
	@../contrib/fastdep-0.15/fastdep $(INCLUDES) --remakedeptarget=.depend $(SOURCES) > .depend

ifneq ($(MAKECMDGOALS),clean)	
-include .depend
endif

