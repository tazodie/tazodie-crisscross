VERSION = 0.5.0
VERSION_MAJOR = 0

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
LINK = $(CXX) -rdynamic
INCLUDES = -I. -I../source -I../source/datastructures
CXXFLAGS = -O2 -Wall $(INCLUDES) -g
NM = nm
STRIP = strip

PCH = header.h.gch

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
	@$(LINK) $+ -lpthread -lstdc++ -L../source -lcrisscross -o $(OUTDIR)/$(OUTBIN)
#	@$(CXX) -shared -Wl,-soname,libcrisscross.so.$(VERSION_MAJOR) -o libcrisscross.so.$(VERSION) $+
	@$(NM) $(OUTDIR)/$(OUTBIN) > $(OUTDIR)/$(OUTBIN).map
	@$(STRIP) $(OUTDIR)/$(OUTBIN)
	@echo done.

$(PCH): header.h
	@echo "Creating precompiled header..."
	@$(CXX) -c header.h -o $(PCH) $(CXXFLAGS)


$(OBJDIR)/%.o: %.cpp
	@test -d $(dir $(OBJDIR)/$<) || mkdir -p $(dir $(OBJDIR)/$<)
	@echo Compiling $<
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: %.c
	@test -d $(dir $(OBJDIR)/$<) || mkdir -p $(dir $(OBJDIR)/$<)
	@echo Compiling $<
	@$(CC) $(CXXFLAGS) -c $< -o $@

.depend:
	@echo Generating dependency information...
	@../contrib/fastdep-0.15/fastdep $(CXXFLAGS) --remakedeptarget=.depend $(SOURCES) > .depend

ifneq ($(MAKECMDGOALS),clean)	
-include .depend
endif

