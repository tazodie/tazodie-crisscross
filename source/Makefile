OBJDIR = obj/linux
OUTDIR = ..
OUTBIN = crisscross-test

SOURCES = \
datastructures/dstack.cpp \
core_console.cpp \
core_cpuid.cpp \
core_debug.cpp \
core_debuglog.cpp \
core_io.cpp \
core_mutex.cpp \
core_system.cpp \
core_thread.cpp \
textreader.cpp \
textwriter.cpp \
main.cpp \
universal_include.cpp

OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)

CXX = g++
CC = gcc
LINK = $(CXX)
CXXFLAGS = -I. -g
NM = nm
STRIP = :

PCH = universal_include.h.gch

all: $(PCH) binary

clean:
	rm -rf obj
	rm -rf .depend
	rm -rf .libs
	rm -f $(OUTDIR)/$(OUTBIN)
	rm -f $(OUTDIR)/$(OUTBIN).map
	rm -f $(PCH)

binary: $(OBJECTS)
	@echo -n "Linking... "
	@$(LINK) -rdynamic $+ -lpthread -lstdc++ -o $(OUTDIR)/$(OUTBIN)
	@$(NM) $(OUTDIR)/$(OUTBIN) > $(OUTDIR)/$(OUTBIN).map
	@$(STRIP) $(OUTDIR)/$(OUTBIN)
	@echo done.

$(PCH): universal_include.h
	@echo "Creating precompiled header..."
	@$(CXX) -c universal_include.h -o $(PCH) $(CXXFLAGS)


$(OBJDIR)/%.o: %.cpp
	@test -d $(dir $(OBJDIR)/$<) || mkdir -p $(dir $(OBJDIR)/$<)
	@echo Compiling $<
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: %.c
	@test -d $(dir $(OBJDIR)/$<) || mkdir -p $(dir $(OBJDIR)/$<)
	@echo Compiling $<
	@$(CC) $(CXXFLAGS) -c $< -o $@

ifneq ($(MAKECMDGOALS),clean)
include auto-depend.mk
endif

