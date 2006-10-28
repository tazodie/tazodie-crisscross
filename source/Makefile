OBJDIR = obj/linux
OUTDIR = ..
OUTBIN = crisscross-test

SOURCES = \
compare.cpp \
core_console.cpp \
core_cpuid.cpp \
core_debug.cpp \
core_debuglog.cpp \
core_filesystem.cpp \
core_io.cpp \
core_mutex.cpp \
core_network.cpp \
core_socket.cpp \
core_system.cpp \
core_thread.cpp \
stopwatch.cpp \
tcpsocket.cpp \
udpsocket.cpp \
textreader.cpp \
textwriter.cpp \
main.cpp \
universal_include.cpp

OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)

CXX = g++
CC = gcc
LINK = $(CXX) -rdynamic
INCLUDES = -I.
CXXFLAGS = -O3 -Wall $(INCLUDES) -g
NM = nm
STRIP = :

PCH = universal_include.h.gch

all: .depend $(PCH) binary
# all: .depend binary

clean:
	rm -rf obj
	rm -f .depend
	rm -rf .libs
	rm -f $(OUTDIR)/$(OUTBIN)
	rm -f $(OUTDIR)/$(OUTBIN).map
	rm -f $(PCH)
	
binary: $(OBJECTS)
	@echo -n "Linking... "
	@$(LINK) $+ -lpthread -lstdc++ -o $(OUTDIR)/$(OUTBIN)
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

.depend:
	@echo Generating dependency information...
	@../contrib/fastdep-0.15/fastdep --remakedeptarget=.depend $(SOURCES) > .depend

ifneq ($(MAKECMDGOALS),clean)	
-include .depend
endif
