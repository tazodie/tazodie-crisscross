OBJDIR = obj/linux

SOURCES = \
core_debug.cpp \
core_console.cpp \
core_mutex.cpp \
core_thread.cpp \
datastructures/dstack.cpp \
textwriter.cpp \
universal_include.cpp \
textreader.cpp \
core_cpuid.cpp \
core_system.cpp \
core_io.cpp \
main.cpp

OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)

CXX = g++
CC = gcc
LINK = $(CXX)
LIBTOOL = libtool
CXXFLAGS = -I. -D_LINUX -O2 -g
NM = nm
STRIP = :

PCH = universal_include.h.gch

all: $(PCH) binary

clean:
	rm -rf obj
	rm -rf .depend
	rm -rf .libs
	rm -f technetium
	rm -f technetium.map
	rm -f $(PCH)

binary: $(OBJECTS)
	@echo -n "Linking... "
	@$(LIBTOOL) --mode=link --quiet $(LINK) $+ -lpthread -lstdc++ -o technetium
	@$(NM) technetium > technetium.map
	@$(STRIP) technetium
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

