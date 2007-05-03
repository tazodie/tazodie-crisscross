include ../common.mk

OBJDIR = obj/linux
OUTDIR = .
ifneq ($(CC_BUILDSTATIC),yes)
OUTNAME = libCrissCross.so
OUTBIN = $(OUTNAME).$(VERSION)
else
OUTNAME = libCrissCross
OUTBIN = $(OUTNAME)-$(VERSION).a
endif
prefix = /usr/local

SOURCES = \
core_console.cpp \
core_cpuid.cpp \
core_databuffer.cpp \
core_debug.cpp \
core_error.cpp \
core_filesystem.cpp \
core_io_reader.cpp \
core_io_writer.cpp \
core_mutex.cpp \
core_network.cpp \
core_socket.cpp \
core_system.cpp \
stopwatch.cpp \
tcpsocket.cpp \
udpsocket.cpp \
textreader.cpp \
textwriter.cpp \
universal_include.cpp

OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)

ifneq ($(GCC_ISCYGMING),yes)
LINK += -rdynamic
endif
INCLUDES += -I.
CXXFLAGS += $(FPIC) $(INCLUDES)

ifeq ($(GCC_MAJOR),4)
PCH = crisscross/universal_include.h
GCH = $(PCH).gch
endif

all: .depend precomp $(OUTDIR)/$(OUTBIN)

precomp: $(GCH)

install: $(OUTDIR)/$(OUTBIN)
	-rm -rf $(prefix)/include/crisscross
	mkdir -p $(prefix)/include/crisscross
	mkdir -p $(prefix)/lib
	cp crisscross/*.gch $(prefix)/include/crisscross/
	cp crisscross/*.h $(prefix)/include/crisscross/
	cp crisscross/*.cpp $(prefix)/include/crisscross/
	cp $(OUTBIN) $(prefix)/lib/
	cd $(prefix)/lib; chmod 755 $(OUTBIN)
	cd $(prefix)/lib; if test -f $(OUTBIN); then \
		rm -f $(OUTNAME) $(OUTNAME).$(VERSION_MAJOR); \
		ln -s $(OUTBIN) $(OUTNAME); \
		ln -s $(OUTBIN) $(OUTNAME).$(VERSION_MAJOR); \
		(ldconfig || true)  >/dev/null 2>&1; \
	fi

clean:
	-rm -rf obj
	-rm -f .depend
	-rm -rf .libs
	-rm -f $(OUTDIR)/$(OUTBIN)
	-rm -f $(OUTDIR)/$(OUTBIN).map
	-rm -f $(GCH)
	-rm -f $(OUTNAME).$(VERSION_MAJOR)
	-rm -f $(OUTNAME)
	
$(OUTDIR)/$(OUTBIN): $(OBJECTS)
ifneq ($(CC_BUILDSTATIC),yes)
ifneq ($(GCC_ISAPPLE),yes)
	$(CXX) -shared -Wl,-soname,$(OUTNAME).$(VERSION_MAJOR) -o $(OUTNAME).$(VERSION) $+
else
	$(CXX) -dynamiclib -Wl,-install_name,$(OUTNAME).$(VERSION_MAJOR) -o $(OUTNAME).$(VERSION) $+
endif
	ln -sf $(OUTNAME).$(VERSION) $(OUTNAME)
	ln -sf $(OUTNAME).$(VERSION) $(OUTNAME).$(VERSION_MAJOR)
else
	$(AR) $@ $+
	-($(RANLIB) $@ || true) >/dev/null 2>&1
endif
	$(NM) $(OUTDIR)/$(OUTBIN) > $(OUTDIR)/$(OUTBIN).map
	$(STRIP) $(OUTDIR)/$(OUTBIN)

$(GCH): $(PCH)
	$(CXX) $(CXXFLAGS) -c $(PCH) -o $(GCH)

$(OBJDIR)/%.o: %.cpp
	@test -d $(dir $(OBJDIR)/$<) || mkdir -p $(dir $(OBJDIR)/$<)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: %.c
	@test -d $(dir $(OBJDIR)/$<) || mkdir -p $(dir $(OBJDIR)/$<)
	$(CC) $(CXXFLAGS) -c $< -o $@

.depend:
ifeq ($(GCC_ISEMULATED),yes)
	../contrib/fastdep-0.15/fastdep --remakedeptarget=.depend $(SOURCES) > .depend
endif

ifneq ($(MAKECMDGOALS),clean)	
-include .depend
endif
