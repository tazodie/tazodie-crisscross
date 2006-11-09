include ../common.mk

OBJDIR = obj/linux
OUTDIR = .
ifneq ($(CC_BUILDSTATIC),yes)
OUTNAME = libcrisscross.so
OUTBIN = $(OUTNAME).$(VERSION)
else
OUTNAME = libcrisscross
OUTBIN = $(OUTNAME)-$(VERSION).a
endif
prefix = /usr

SOURCES = \
compare.cpp \
core_console.cpp \
core_cpuid.cpp \
core_debug.cpp \
core_filesystem.cpp \
core_io_reader.cpp \
core_io_writer.cpp \
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

CCDV = ../tools/ccdv/ccdv.bin
ifneq ($(GCC_ISCYGMING),yes)
LINK += -rdynamic
endif
INCLUDES += -I.
CXXFLAGS += $(FPIC) $(INCLUDES)

ifeq ($(GCC_MAJOR),4)
PCH = universal_include.h.gch
endif

all: .depend precomp $(OUTDIR)/$(OUTBIN)

precomp: $(PCH)

install: $(OUTDIR)/$(OUTBIN)
	-rm -rf $(prefix)/include/crisscross
	mkdir -p $(prefix)/include/crisscross
	mkdir -p $(prefix)/lib
	cp crisscross/*.h $(prefix)/include/crisscross/
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
	-rm -f $(PCH)
	-rm -f $(OUTNAME).$(VERSION_MAJOR)
	-rm -f $(OUTNAME)
	
$(OUTDIR)/$(OUTBIN): $(OBJECTS)
	@echo -n "Creating library... "
ifneq ($(CC_BUILDSTATIC),yes)
ifneq ($(GCC_ISAPPLE),yes)
	@$(CCDV) $(CXX) -shared -Wl,-soname,$(OUTNAME).$(VERSION_MAJOR) -o $(OUTNAME).$(VERSION) $+
else
	@$(CCDV) $(CXX) -dynamiclib -Wl,-install_name,$(OUTNAME).$(VERSION_MAJOR) -o $(OUTNAME).$(VERSION) $+
endif
	@ln -sf $(OUTNAME).$(VERSION) $(OUTNAME)
	@ln -sf $(OUTNAME).$(VERSION) $(OUTNAME).$(VERSION_MAJOR)
else
	@$(AR) $@ $+
	-@($(RANLIB) $@ || true) >/dev/null 2>&1
endif
	@$(NM) $(OUTDIR)/$(OUTBIN) > $(OUTDIR)/$(OUTBIN).map
	@$(STRIP) $(OUTDIR)/$(OUTBIN)

$(PCH): crisscross/universal_include.h
	@$(CCDV) $(CXX) -c crisscross/universal_include.h -o $(PCH) $(CXXFLAGS)


$(OBJDIR)/%.o: %.cpp
	@test -d $(dir $(OBJDIR)/$<) || mkdir -p $(dir $(OBJDIR)/$<)
	@$(CCDV) $(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: %.c
	@test -d $(dir $(OBJDIR)/$<) || mkdir -p $(dir $(OBJDIR)/$<)
	@$(CCDV) $(CC) $(CXXFLAGS) -c $< -o $@

.depend:
ifeq ($(GCC_ISEMULATED),yes)
	@../contrib/fastdep-0.15/fastdep --remakedeptarget=.depend $(SOURCES) > .depend
endif

ifneq ($(MAKECMDGOALS),clean)	
-include .depend
endif
