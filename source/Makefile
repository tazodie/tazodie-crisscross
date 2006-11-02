VERSION = 0.5.0
VERSION_MAJOR = 0

OBJDIR = obj/linux
OUTDIR = .
OUTNAME = libcrisscross.so
OUTBIN = $(OUTNAME).$(VERSION)
prefix = /usr

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
universal_include.cpp

OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)

CXX = g++
CC = gcc
LINK = $(CXX) -rdynamic
INCLUDES = -I.
CXXFLAGS = -O2 -fPIC -Wall $(INCLUDES) -g
NM = nm
STRIP = :

PCH = universal_include.h.gch

# all: .depend $(PCH) $(OUTDIR)/$(OUTBIN)
all: .depend $(OUTDIR)/$(OUTBIN)

install: $(OUTDIR)/$(OUTBIN)
	mkdir -p $(prefix)/include/crisscross
	mkdir -p $(prefix)/include/crisscross/datastructures
	mkdir -p $(prefix)/lib
	cp *.h $(prefix)/include/crisscross/
	cp datastructures/* $(prefix)/include/crisscross/datastructures
	cp $(OUTBIN) $(prefix)/lib/
	cd $(prefix)/lib; chmod 755 $(OUTBIN)
	cd $(prefix)/lib; if test -f $(OUTBIN); then \
		rm -f $(OUTNAME) $(OUTNAME).$(VERSION_MAJOR); \
		ln -s $(OUTBIN) $(OUTNAME); \
		ln -s $(OUTBIN) $(OUTNAME).$(VERSION_MAJOR); \
		(ldconfig || true)  >/dev/null 2>&1; \
	fi

clean:
	rm -rf obj
	rm -f .depend
	rm -rf .libs
	rm -f $(OUTDIR)/$(OUTBIN)
	rm -f $(OUTDIR)/$(OUTBIN).map
	rm -f $(PCH)
	
$(OUTDIR)/$(OUTBIN): $(OBJECTS)
	@echo -n "Creating library... "
	@$(CXX) -shared -Wl,-soname,libcrisscross.so.$(VERSION_MAJOR) -o libcrisscross.so.$(VERSION) $+
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
